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

static char	*get_cmd_path(t_cmd *cmd, char **env)
{
	char	*path;

	if (ft_strchr(cmd->args[0], '/'))
		path = handle_path_cmd(cmd->args[0]);
	else
	{
		path = handle_local_cmd(cmd->args[0], env);
		if (!path)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->args[0], 2);
			ft_putendl_fd(": command not found", 2);
			exit(127);
		}
	}
	return (path);
}

static void	exec_cmd(t_cmd *cmd, char **env)
{
	char	*path;

	if (!cmd->args || !cmd->args[0])
		exit(0);
	if (cmd->args[0][0] == '\0')
	{
		ft_putendl_fd("minishell: : command not found", 2);
		exit(127);
	}
	path = get_cmd_path(cmd, env);
	execve(path, cmd->args, env);
	if (errno == ENOEXEC || errno == EACCES)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": command not found", 2);
		free(path);
		exit(127);
	}
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
	if (handle_redir(cmd->redir) != 0)
		exit(1);
	close_all_fds();
	if (is_builtin(cmd->args[0]))
		exit(run_builtin(cmd, sh));
	exec_cmd(cmd, sh->env);
}

static void	close_and_update(int *in, t_cmd *cmd, int fd[2])
{
	if (*in != STDIN_FILENO)
		close(*in);
	close_heredoc_fds(cmd->redir);
	if (cmd->next)
	{
		close(fd[1]);
		*in = fd[0];
	}
	else
		*in = STDIN_FILENO;
}

pid_t	pipe_and_fork(t_cmd *cmd, t_shell *sh, int *in)
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
	{
		if (cmd->next)
			close(fd[0]);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		child_process(cmd, sh, *in, out);
	}
	close_and_update(in, cmd, fd);
	return (pid);
}
