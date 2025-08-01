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
