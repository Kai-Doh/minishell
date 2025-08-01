/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 00:00:00 by ktiomico          #+#    #+#             */
/*   Updated: 2025/08/01 00:00:01 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_env_var_index(char **env, const char *key, size_t key_len)
{
	int	i;

	if (!env || !key)
		return (-1);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, key_len) && env[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	**dup_env(char **env)
{
	int		i;
	char	**new;

	i = 0;
	while (env[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new[i] = ft_strdup(env[i]);
		if (!new[i])
		{
			ft_free_split(new);
			return (NULL);
		}
		i++;
	}
	new[i] = NULL;
	return (new);
}

char	**ft_strs_add(char **env, char *new_entry)
{
	char	**new;
	int		len;
	int		i;

	len = 0;
	while (env && env[len])
		len++;
	new = malloc(sizeof(char *) * (len + 2));
	if (!new)
		return (NULL);
	i = -1;
	while (++i < len)
	{
		new[i] = ft_strdup(env[i]);
		if (!new[i])
			return (ft_free_split(new), NULL);
	}
	new[i] = ft_strdup(new_entry);
	if (!new[i])
		return (ft_free_split(new), NULL);
	new[i + 1] = NULL;
	ft_free_split(env);
	return (new);
}

static int	copy_env_skipping_index(char **env, char **new, int index)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (i != index)
		{
			new[j] = ft_strdup(env[i]);
			if (!new[j])
				return (j);
			j++;
		}
		i++;
	}
	new[j] = NULL;
	return (-1);
}

char	**ft_strs_remove(char **env, int index)
{
	char	**new;
	int		len;
	int		fail_idx;

	len = 0;
	while (env && env[len])
		len++;
	new = malloc(sizeof(char *) * len);
	if (!new)
		return (NULL);
	fail_idx = copy_env_skipping_index(env, new, index);
	if (fail_idx >= 0)
	{
		while (fail_idx-- > 0)
			free(new[fail_idx]);
		return (free(new), NULL);
	}
	ft_free_split(env);
	return (new);
}
