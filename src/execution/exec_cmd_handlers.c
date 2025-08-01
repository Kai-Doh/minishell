/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 00:00:00 by ktiomico          #+#    #+#             */
/*   Updated: 2025/08/01 00:00:01 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_stat_error(char *cmd_name, t_shell *sh)
{
	perror(cmd_name);
	if (sh)
		cleanup_and_exit_child(sh, sh->all_cmds, sh->all_tokens, 127);
	else
		cleanup_and_exit_child(NULL, NULL, NULL, 127);
}

static void	handle_directory_error(char *cmd_name, t_shell *sh)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putendl_fd(": Is a directory", 2);
	if (sh)
		cleanup_and_exit_child(sh, sh->all_cmds, sh->all_tokens, 126);
	else
		cleanup_and_exit_child(NULL, NULL, NULL, 126);
}

static void	handle_access_error(char *cmd_name, t_shell *sh)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putendl_fd(": command not found", 2);
	if (sh)
		cleanup_and_exit_child(sh, sh->all_cmds, sh->all_tokens, 127);
	else
		cleanup_and_exit_child(NULL, NULL, NULL, 127);
}

char	*handle_path_cmd(char *cmd_name, t_shell *sh)
{
	struct stat	st;

	if (stat(cmd_name, &st) != 0)
		handle_stat_error(cmd_name, sh);
	if (S_ISDIR(st.st_mode))
		handle_directory_error(cmd_name, sh);
	if (access(cmd_name, X_OK) != 0)
		handle_access_error(cmd_name, sh);
	return (ft_strdup(cmd_name));
}

char	*handle_local_cmd(char *cmd_name, char **env)
{
	return (find_command_path(cmd_name, env));
}
