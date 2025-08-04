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

void	ft_free_split(char **arr);
char	*join_path(char *dir, char *cmd);
char	*get_path_variable(char **env);

char	*find_command_path(char *cmd, char **env)
{
	char	**paths;
	char	*path_val;
	char	*full;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_val = get_path_variable(env);
	if (!path_val)
		return (NULL);
	paths = ft_split(path_val, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		full = join_path(paths[i], cmd);
		if (full && access(full, X_OK) == 0)
			return (ft_free_split(paths), full);
		free(full);
	}
	ft_free_split(paths);
	return (NULL);
}

void	ft_free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	free(arr);
}

char	*join_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full);
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
