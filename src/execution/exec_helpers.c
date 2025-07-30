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
	dup2(save_in, STDIN_FILENO);
	dup2(save_out, STDOUT_FILENO);
	close(save_in);
	close(save_out);
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
	if (handle_redir(cmd->redir) != 0)
		sh->last_exit_status = 1;
	else
		sh->last_exit_status = run_builtin(cmd, sh);
	return (sh->last_exit_status);
}
