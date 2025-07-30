/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github <github@kaidoh.ch>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 23:39:29 by github            #+#    #+#             */
/*   Updated: 2025/06/24 23:39:31 by github           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_redir	*add_redir(t_token **tok, t_shell *sh)
{
	t_redir	*r;

	r = NULL;
	r = malloc(sizeof(t_redir));
	if (!r)
		return (NULL);
	r->type = (*tok)->type;
	r->heredoc_fd = -1;
	*tok = (*tok)->next;
	if (!*tok)
	{
		free(r);
		return (NULL);
	}
	r->file = expand_word((*tok)->content, sh);
	if (r->type == HEREDOC)
		r->heredoc_fd = create_heredoc(r->file);
	r->next = NULL;
	*tok = (*tok)->next;
	return (r);
}

static int	fill_command(t_cmd *cmd, t_token **tok, t_shell *sh)
{
	t_redir	*last;

	last = NULL;
	while (*tok && (*tok)->type != PIPE)
	{
		if ((*tok)->type == WORD)
		{
			if (handle_word_token(cmd, tok, sh))
				return (1);
		}
		else if ((*tok)->type >= REDIR_IN && (*tok)->type <= APPEND)
			handle_redirr(cmd, tok, sh, &last);
		else
			*tok = (*tok)->next;
	}
	return (0);
}

t_cmd	*add_command(t_token **tok, t_shell *sh)
{
	t_cmd	*cmd;

	cmd = NULL;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redir = NULL;
	cmd->next = NULL;
	if (fill_command(cmd, tok, sh))
	{
		free_cmds(cmd);
		return (NULL);
	}
	if (*tok && (*tok)->type == PIPE)
		*tok = (*tok)->next;
	return (cmd);
}

t_cmd	*parse(t_token *tok, t_shell *sh)
{
	t_cmd	*first;
	t_cmd	*last;
	t_cmd	*new;

	first = NULL;
	last = NULL;
	new = NULL;
	if (validate_syntax(tok, sh))
		return (NULL);
	while (tok)
	{
		new = add_command(&tok, sh);
		if (!new)
		{
			free_cmds(first);
			return (NULL);
		}
		if (!first)
			first = new;
		else
			last->next = new;
		last = new;
	}
	return (first);
}
