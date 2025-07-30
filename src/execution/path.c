/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:07:01 by ktiomico          #+#    #+#             */
/*   Updated: 2025/04/29 14:11:12 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_path_variable(char **env);
int			is_valid_executable(char *full);
static char	*check_current_dir(char *cmd);
static char	*search_in_paths(char *cmd, char **env);

char	*find_command_path(char *cmd, char **env)
{
	char	*result;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	result = check_current_dir(cmd);
	if (result)
		return (result);
	return (search_in_paths(cmd, env));
}

static char	*check_current_dir(char *cmd)
{
	struct stat	st;

	if (stat(cmd, &st) == 0 && !S_ISDIR(st.st_mode))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
	}
	return (NULL);
}

static char	*search_in_paths(char *cmd, char **env)
{
	char	**paths;
	char	*path_val;
	char	*full;
	int		i;

	path_val = get_path_variable(env);
	if (!path_val && is_valid_executable(cmd))
		return (ft_strdup(cmd));
	if (!path_val)
		return (NULL);
	paths = ft_split(path_val, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		full = join_path(paths[i], cmd);
		if (is_valid_executable(full))
			return (ft_free_split(paths), full);
		free(full);
	}
	return (ft_free_split(paths), NULL);
}

int	is_valid_executable(char *full)
{
	struct stat	st;

	if (!full || access(full, X_OK) != 0)
		return (0);
	if (stat(full, &st) != 0 || S_ISDIR(st.st_mode))
		return (0);
	return (1);
}

char	*get_path_variable(char **env)
{
	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
			return (*env + 5);
		env++;
	}
	return (NULL);
}
