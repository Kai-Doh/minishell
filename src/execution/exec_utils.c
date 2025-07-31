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
		cleanup_and_exit_child(NULL, NULL, NULL, 127);
	}
	if (S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_name, 2);
		ft_putendl_fd(": Is a directory", 2);
		cleanup_and_exit_child(NULL, NULL, NULL, 126);
	}
	if (access(cmd_name, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_name, 2);
		ft_putendl_fd(": command not found", 2);
		cleanup_and_exit_child(NULL, NULL, NULL, 127);
	}
	return (ft_strdup(cmd_name));
}

char	*handle_local_cmd(char *cmd_name, char **env)
{
	return (find_command_path(cmd_name, env));
}

static int	exec_single_builtin(t_cmd *cmd, t_shell *sh)
{
	int	save_in;
	int	save_out;
	int	status;

	save_in = dup(STDIN_FILENO);
	save_out = dup(STDOUT_FILENO);
	if (save_in < 0 || save_out < 0)
	{
		if (save_in >= 0)
			close(save_in);
		if (save_out >= 0)
			close(save_out);
		sh->last_exit_status = 1;
		return (1);
	}
	if (handle_redir(cmd->redir, sh) != 0)
	{
		restore_fds(save_in, save_out);
		sh->last_exit_status = 1;
		return (1);
	}
	close_all_heredoc_fds(sh);
	if (cmd->args[0] && !ft_strncmp(cmd->args[0], "exit", 5))
	{
		restore_fds(save_in, save_out);
		status = run_builtin(cmd, sh);
	}
	else
	{
		status = run_builtin(cmd, sh);
		sh->last_exit_status = status;
		restore_fds(save_in, save_out);
	}
	return (status);
}

int	execute_pipeline(t_cmd *cmd, t_shell *sh)
{
	int		in;
	pid_t	last_pid;
	t_cmd	*current;

	in = STDIN_FILENO;
	current = cmd;
	while (current)
	{
		last_pid = pipe_and_fork(current, sh, &in);
		current = current->next;
	}
	wait_all(last_pid, sh);
	close_all_heredoc_fds(sh);
	cleanup_heredoc_tracking(sh);
	init_heredoc_tracking(sh);
	return (sh->last_exit_status);
}

int	execute(t_cmd *cmd, t_shell *sh)
{
	int	result;

	if (!cmd)
	{
		sh->last_exit_status = 0;
		return (0);
	}
	result = handle_empty_cmd(cmd, sh);
	if (result != -1)
		return (result);
	if (cmd && !cmd->next && cmd->args && cmd->args[0]
		&& is_builtin(cmd->args[0]))
	{
		if (!ft_strncmp(cmd->args[0], "exit", 5))
			result = handle_exit_builtin(cmd, sh);
		else
			result = exec_single_builtin(cmd, sh);
		cleanup_heredoc_tracking(sh);
		init_heredoc_tracking(sh);
		return (result);
	}
	return (execute_pipeline(cmd, sh));
}
