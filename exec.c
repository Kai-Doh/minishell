/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:58:26 by ktiomico          #+#    #+#             */
/*   Updated: 2025/04/29 15:51:41 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_cmd(t_cmd *cmd, char **env)
{
	char	*path;

	if (!cmd->args || !cmd->args[0])
		exit(0);
	path = find_command_path(cmd->args[0], env);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(cmd->args[0], 2);
		exit(127);
	}
	execve(path, cmd->args, env);
	perror(path);
	free(path);
	exit(126);
}

static void	child_process(t_cmd *cmd, t_shell *sh, int in, int out)
{
	if (in != STDIN_FILENO)
	{
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (out != STDOUT_FILENO)
	{
		dup2(out, STDOUT_FILENO);
		close(out);
	}
	handle_redir(cmd->redir);
	if (is_builtin(cmd->args[0]))
		exit(run_builtin(cmd, sh));
	exec_cmd(cmd, sh->env);
}

static void	run_child(t_cmd *cmd, t_shell *sh, int in, int out)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	child_process(cmd, sh, in, out);
}

void	pipe_and_fork(t_cmd *cmd, t_shell *sh, int *in)
{
	int		fd[2];
	pid_t	pid;
	int		out;

	if (cmd->next && pipe(fd) == -1)
		exit_msg("Pipe error", 1, NULL);
	if (cmd->next)
		out = fd[1];
	else
		out = STDOUT_FILENO;
	pid = fork();
	if (pid < 0)
		exit_msg("Fork failed", 1, NULL);
	if (pid == 0)
		run_child(cmd, sh, *in, out);
	if (*in != STDIN_FILENO)
		close(*in);
	if (cmd->next)
	{
		close(fd[1]);
		*in = fd[0];
	}
}
