/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:00:00 by ktiomico          #+#    #+#             */
/*   Updated: 2025/07/28 16:00:00 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_env_var(char **env, char *key)
{
	int	i;
	int	key_len;

	if (!env || !key)
		return (-1);
	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, key_len) && env[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static char	*extract_key(char *env_entry)
{
	char	*equal;

	equal = ft_strchr(env_entry, '=');
	if (!equal)
		return (NULL);
	return (ft_substr(env_entry, 0, equal - env_entry));
}

static void	merge_env_entry(char **merged_env, char *env_entry, char *key)
{
	int	sys_idx;

	sys_idx = find_env_var(merged_env, key);
	if (sys_idx >= 0)
	{
		free(merged_env[sys_idx]);
		merged_env[sys_idx] = ft_strdup(env_entry);
	}
}

void	update_env_from_system(t_shell *sh)
{
	extern char	**environ;
	char		**merged_env;
	char		*key;
	int			i;

	merged_env = dup_env(environ);
	if (!merged_env)
		return ;
	i = 0;
	while (sh->env[i])
	{
		key = extract_key(sh->env[i]);
		if (key)
		{
			if (find_env_var(merged_env, key) >= 0)
				merge_env_entry(merged_env, sh->env[i], key);
			else
				merged_env = ft_strs_add(merged_env, sh->env[i]);
			free(key);
		}
		i++;
	}
	ft_free_split(sh->env);
	sh->env = merged_env;
}
