/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github <github@kaidoh.ch>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 00:00:00 by github            #+#    #+#             */
/*   Updated: 2025/07/30 00:00:02 by github           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_fds(int save_in, int save_out)
{
	if (save_in >= 0)
	{
		dup2(save_in, STDIN_FILENO);
		close(save_in);
	}
	if (save_out >= 0)
	{
		dup2(save_out, STDOUT_FILENO);
		close(save_out);
	}
}

int	handle_empty_cmd(t_cmd *cmd, t_shell *sh)
{
	if ((!cmd->args || !cmd->args[0] || cmd->args[0][0] == '\0') && !cmd->redir)
	{
		if (cmd->args && cmd->args[0] && cmd->args[0][0] == '\0')
			sh->last_exit_status = 127;
		else
			sh->last_exit_status = 0;
		return (0);
	}
	if ((!cmd->args || !cmd->args[0] || cmd->args[0][0] == '\0') && cmd->redir)
		return (execute_pipeline(cmd, sh));
	return (-1);
}

int	handle_exit_builtin(t_cmd *cmd, t_shell *sh)
{
	if (handle_redir(cmd->redir, sh) != 0)
		sh->last_exit_status = 1;
	else
		sh->last_exit_status = run_builtin(cmd, sh);
	return (sh->last_exit_status);
}

void	close_heredoc_fds(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == HEREDOC && redir->heredoc_fd >= 0)
		{
			close(redir->heredoc_fd);
			redir->heredoc_fd = -1;
		}
		redir = redir->next;
	}
}

void	init_heredoc_tracking(t_shell *sh)
{
	sh->heredoc_fds = NULL;
	sh->heredoc_count = 0;
}
