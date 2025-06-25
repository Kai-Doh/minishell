/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github <github@kaidoh.ch>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 22:59:42 by github            #+#    #+#             */
/*   Updated: 2025/06/24 22:59:44 by github           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_single_builtin(t_cmd *cmd, t_shell *sh)
{
	int	save_in;
	int	save_out;
	int	status;

	save_in = dup(STDIN_FILENO);
	save_out = dup(STDOUT_FILENO);
	handle_redir(cmd->redir);
	status = run_builtin(cmd, sh);
	sh->last_exit_status = status;
	dup2(save_in, STDIN_FILENO);
	dup2(save_out, STDOUT_FILENO);
	close(save_in);
	close(save_out);
	return (status);
}

static void	wait_all(pid_t *last_status, t_shell *sh)
{
	int	status;

	while (wait(&status) > 0)
		*last_status = status;
	if (WIFEXITED(*last_status))
		sh->last_exit_status = WEXITSTATUS(*last_status);
	else
		sh->last_exit_status = 1;
}

int	execute(t_cmd *cmd, t_shell *sh)
{
	int	in;
	int	last;

	if (cmd && !cmd->next && is_builtin(cmd->args[0]))
		return (exec_single_builtin(cmd, sh));
	in = STDIN_FILENO;
	while (cmd)
	{
		pipe_and_fork(cmd, sh, &in);
		cmd = cmd->next;
	}
	last = 0;
	wait_all(&last, sh);
	return (sh->last_exit_status);
}
