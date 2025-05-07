/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thofstet <thofstet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:52:54 by thofstet          #+#    #+#             */
/*   Updated: 2025/05/07 17:52:54 by thofstet         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_msg(char *msg, int code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd(msg, 2);
	exit(code);
}

void	free_tokens(t_token *tok)
{
	t_token	*tmp;

	while (tok)
	{
		tmp = tok->next;
		free(tok->content);
		free(tok);
		tok = tmp;
	}
}

void	free_cmds(t_cmd *cmd)
{
	t_cmd		*tmp;
	t_redir		*r;
	t_redir		*r_next;
	int			i;

	while (cmd)
	{
		tmp = cmd->next;
		i = 0;
		while (cmd->args && cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
		r = cmd->redir;
		while (r)
		{
			r_next = r->next;
			free(r->file);
			free(r);
			r = r_next;
		}
		free(cmd);
		cmd = tmp;
	}
}