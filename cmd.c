/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:38:11 by ktiomico          #+#    #+#             */
/*   Updated: 2025/04/17 13:38:19 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_path(char *dir, char *cmd)
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

char	*find_cmd_path(char *cmd, char **env)
{
	char	**paths;
	char	*path_val;
	char	*full;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	while (*env && ft_strncmp(*env, "PATH=", 5))
		env++;
	if (!*env)
		return (NULL);
	path_val = *env + 5;
	paths = ft_split(path_val, ':');
	i = -1;
	while (paths && paths[++i])
	{
		full = join_path(paths[i], cmd);
		if (full && access(full, X_OK) == 0)
			return (ft_split_free(paths), full);
		free(full);
	}
	ft_split_free(paths);
	return (NULL);
}
