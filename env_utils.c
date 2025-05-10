/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thofstet <thofstet>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:11:41 by thofstet          #+#    #+#             */
/*   Updated: 2025/05/10 17:15:08 by thofstet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env_var(char ***envp, const char *key, const char *value)
{
	int		i;
	char	*prefix;
	char	*new_var;

	if (!envp || !*envp || !key || !value)
		return ;
	prefix = ft_strjoin(key, "=");
	if (!prefix)
		return ;
	new_var = ft_strjoin(prefix, value);
	free(prefix);
	if (!new_var)
		return ;
	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], key, ft_strlen(key)) == 0)
		{
			if ((*envp)[i][ft_strlen(key)] == '=')
			{
				free((*envp)[i]);
				(*envp)[i] = new_var;
				return ;
			}
		}
		i++;
	}
	char	**new_env;

	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
	{
		free(new_var);
		return ;
	}
	int	j;

	j = 0;
	while (j < i)
	{
		new_env[j] = (*envp)[j];
		j++;
	}
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	free(*envp);
	*envp = new_env;
}

char	**copy_env(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			// Libère ce qui a déjà été dupliqué pour éviter les fuites
			while (--i >= 0)
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	free_env(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}
