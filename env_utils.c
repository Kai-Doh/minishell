/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thofstet <thofstet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:54:48 by thofstet          #+#    #+#             */
/*   Updated: 2025/05/07 17:54:48 by thofstet         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	update_env_var(char ***envp, const char *key, const char *value)
{
	int		i;
	char	*prefix;
	char	*new_var;

	if (!envp || !*envp || !key || !value)
		return;

	prefix = ft_strjoin(key, "=");
	if (!prefix)
		return;
	new_var = ft_strjoin(prefix, value);
	free(prefix);
	if (!new_var)
		return;

	for (i = 0; (*envp)[i]; i++)
	{
		if (ft_strncmp((*envp)[i], key, ft_strlen(key)) == 0
			&& (*envp)[i][ft_strlen(key)] == '=')
		{
			free((*envp)[i]);
			(*envp)[i] = new_var;
			return;
		}
	}

	char **new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
	{
		free(new_var);
		return;
	}
	for (int j = 0; j < i; j++)
		new_env[j] = (*envp)[j];
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	free(*envp);
	*envp = new_env;
}
char	**copy_env(char **env)
{
	int		i;
	char	**new_env;

	for (i = 0; env[i]; i++)
		;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	for (i = 0; env[i]; i++)
		new_env[i] = ft_strdup(env[i]);
	new_env[i] = NULL;
	return (new_env);
}

void	free_env(char **env)
{
	int	i;

	if (!env)
		return;
	for (i = 0; env[i]; i++)
		free(env[i]);
	free(env);
}
