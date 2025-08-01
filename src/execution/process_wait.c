/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_wait.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github <github@kaidoh.ch>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 23:55:00 by github            #+#    #+#             */
/*   Updated: 2025/06/24 23:55:02 by github           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wait_for_processes(pid_t last_pid)
{
	int		status;
	pid_t	pid;
	int		last_status;

	last_status = 0;
	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last_pid)
			last_status = status;
		pid = wait(&status);
	}
	return (last_status);
}

static void	handle_process_exit(int last_status, t_shell *sh)
{
	if (WIFEXITED(last_status))
		sh->last_exit_status = WEXITSTATUS(last_status);
	else if (WIFSIGNALED(last_status) && WTERMSIG(last_status) == SIGINT)
	{
		sh->last_exit_status = 130;
		write(1, "\n", 1);
	}
	else if (WIFSIGNALED(last_status) && WTERMSIG(last_status) == SIGQUIT)
	{
		sh->last_exit_status = 131;
		write(1, "Quit\n", 5);
	}
	else
		sh->last_exit_status = 1;
}

void	wait_all(pid_t last_pid, t_shell *sh)
{
	int	last_status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	last_status = wait_for_processes(last_pid);
	setup_signals();
	handle_process_exit(last_status, sh);
}
