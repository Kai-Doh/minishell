/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:04:16 by ktiomico          #+#    #+#             */
/*   Updated: 2025/04/17 13:49:44 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_msg(char *msg, int code)
{
	printf(RED "%s\n", msg);
	exit(code);
}

void	ft_tokclear(t_token **lst)
{
	t_token	*tmp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
}

bool	tok_is_builtin_exit(t_token *tok)
{
	if (!tok || tok->type != WORD)
		return (false);
	if (!tok->next)
		return (ft_strncmp(tok->content, "exit", 5) == 0);
	return (false);
}

char	**tok_to_argv(t_token *tok, int *has_pipe, t_token **next)
{
	int		wc;
	t_token	*tmp;
	char	**argv;

	tmp = tok;
	wc = 0;
	while (tmp && tmp->type == WORD && ++wc)
		tmp = tmp->next;
	argv = ft_calloc(wc + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	wc = 0;
	while (tok && tok->type == WORD)
	{
		argv[wc++] = tok->content;
		tok = tok->next;
	}
	*has_pipe = (tok && tok->type == PIPE);
	if (*has_pipe)
		*next = tok->next;
	else
		*next = tok;
	return (argv);
}
