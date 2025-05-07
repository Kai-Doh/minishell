/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:58:00 by ktiomico          #+#    #+#             */
/*   Updated: 2025/04/29 14:16:30 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(t_token *tok)
{
	int	count;

	count = 0;
	while (tok && tok->type == WORD)
	{
		count++;
		tok = tok->next;
	}
	return (count);
}

static char	**fill_args(t_token **tok)
{
	char	**args;
	int		n;
	int		i;

	n = count_args(*tok);
	args = malloc(sizeof(char *) * (n + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (i < n)
	{
		args[i++] = ft_strdup((*tok)->content);
		*tok = (*tok)->next;
	}
	args[i] = NULL;
	return (args);
}

static t_redir	*add_redir(t_token **tok)
{
	t_redir	*r;

	r = malloc(sizeof(t_redir));
	if (!r)
		return (NULL);
	r->type = (*tok)->type;
	*tok = (*tok)->next;
	if (!*tok)
		return (NULL);
	r->file = ft_strdup((*tok)->content);
	r->next = NULL;
	*tok = (*tok)->next;
	return (r);
}

static t_cmd	*add_command(t_token **tok)
{
	t_cmd	*cmd;
	t_redir	*r;
	t_redir	*last;

	cmd = malloc(sizeof(t_cmd));
	cmd->args = fill_args(tok);
	cmd->redir = NULL;
	cmd->next = NULL;
	last = NULL;
	while (*tok && (*tok)->type != PIPE)
	{
		if ((*tok)->type >= REDIR_IN && (*tok)->type <= APPEND)
		{
			r = add_redir(tok);
			if (!cmd->redir)
				cmd->redir = r;
			else
				last->next = r;
			last = r;
		}
		else
			*tok = (*tok)->next;
	}
	if (*tok && (*tok)->type == PIPE)
		*tok = (*tok)->next;
	return (cmd);
}

t_cmd	*parse(t_token *tok)
{
	t_cmd	*first;
	t_cmd	*last;
	t_cmd	*new;

	first = NULL;
	last = NULL;
	while (tok)
	{
		new = add_command(&tok);
		if (!first)
			first = new;
		else
			last->next = new;
		last = new;
	}
	return (first);
}
