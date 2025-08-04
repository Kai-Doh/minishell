/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 22:59:42 by ktiomico          #+#    #+#             */
/*   Updated: 2025/06/24 22:59:44 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_path_cmd(char *cmd_name)
{
	struct stat	st;

	if (stat(cmd_name, &st) != 0)
	{
		perror(cmd_name);
		exit(127);
	}
	if (S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_name, 2);
		ft_putendl_fd(": Is a directory", 2);
		exit(126);
	}
	return (ft_strdup(cmd_name));
}

char	*handle_local_cmd(char *cmd_name, char **env)
{
	struct stat	st;

	if (access(cmd_name, F_OK) == 0)
	{
		if (stat(cmd_name, &st) == 0 && S_ISDIR(st.st_mode))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd_name, 2);
			ft_putendl_fd(": command not found", 2);
			exit(127);
		}
		if (access(cmd_name, X_OK) != 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd_name, 2);
			ft_putendl_fd(": Permission denied", 2);
			exit(126);
		}
		return (ft_strdup(cmd_name));
	}
	return (find_command_path(cmd_name, env));
}

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

static void	wait_all(pid_t last_pid, t_shell *sh)
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
	if (WIFEXITED(last_status))
		sh->last_exit_status = WEXITSTATUS(last_status);
	else
		sh->last_exit_status = 1;
}

int	execute(t_cmd *cmd, t_shell *sh)
{
	int		in;
	pid_t	last_pid;
	t_cmd	*current;

	if (!cmd || !cmd->args || !cmd->args[0])
	{
		sh->last_exit_status = 0;
		return (0);
	}
	if (cmd && !cmd->next && cmd->args && cmd->args[0]
		&& is_builtin(cmd->args[0]))
		return (exec_single_builtin(cmd, sh));
	in = STDIN_FILENO;
	current = cmd;
	while (current)
	{
		last_pid = pipe_and_fork(current, sh, &in);
		current = current->next;
	}
	wait_all(last_pid, sh);
	return (sh->last_exit_status);
}
