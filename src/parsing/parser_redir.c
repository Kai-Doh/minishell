/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github <github@kaidoh.ch>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 00:00:00 by github            #+#    #+#             */
/*   Updated: 2025/07/30 00:00:02 by github           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_heredoc_node(t_redir *curr)
{
	if (curr->heredoc_fd >= 0)
		close(curr->heredoc_fd);
	free(curr->file);
	free(curr);
}

void	remove_previous_heredocs(t_cmd *cmd)
{
	t_redir	*prev;
	t_redir	*curr;

	prev = NULL;
	curr = cmd->redir;
	while (curr)
	{
		if (curr->type == HEREDOC)
		{
			if (prev)
				prev->next = curr->next;
			else
				cmd->redir = curr->next;
			free_heredoc_node(curr);
			if (prev)
				curr = prev->next;
			else
				curr = cmd->redir;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

void	handle_redirr(t_cmd *cmd, t_token **tok, t_shell *sh, t_redir **last)
{
	t_redir	*r;

	r = add_redir(tok, sh);
	if (!r)
		return ;
	if (r->type == HEREDOC)
		remove_previous_heredocs(cmd);
	if (!cmd->redir)
		cmd->redir = r;
	else if (*last)
		(*last)->next = r;
	*last = r;
}
