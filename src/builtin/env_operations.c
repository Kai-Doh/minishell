/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 00:00:00 by ktiomico          #+#    #+#             */
/*   Updated: 2025/07/31 00:00:00 by ktiomico         ###   ########.fr       */
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

static void	free_partial(char **arr, int n)
{
	while (n-- > 0)
		free(arr[n]);
	free(arr);
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
	i = 0;
	while (i < len)
	{
		new[i] = ft_strdup(env[i]);
		if (!new[i])
			return (free_partial(new, i), NULL);
		i++;
	}
	new[i] = ft_strdup(new_entry);
	if (!new[i])
		return (free_partial(new, i), NULL);
	new[i + 1] = NULL;
	ft_free_split(env);
	return (new);
}

char	**ft_strs_remove(char **env, int index)
{
	char	**new;
	int		len;
	int		i;
	int		j;

	len = 0;
	while (env && env[len])
		len++;
	new = malloc(sizeof(char *) * len);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (i != index)
		{
			new[j] = ft_strdup(env[i]);
			if (!new[j])
				return (free_partial(new, j), NULL);
			j++;
		}
		i++;
	}
	new[j] = NULL;
	ft_free_split(env);
	return (new);
}

void	set_env_var(t_shell *sh, const char *key, const char *value)
{
	int		idx;
	size_t	key_len;
	char	*entry;
	char	*tmp;

	key_len = ft_strlen(key);
	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return ;
	entry = ft_strjoin(tmp, value);
	free(tmp);
	if (!entry)
		return ;
	idx = find_env_var_index(sh->env, key, key_len);
	if (idx != -1)
	{
		free(sh->env[idx]);
		sh->env[idx] = entry;
		return ;
	}
	sh->env = ft_strs_add(sh->env, entry);
	free(entry);
}

void	process_append_assignment(char *arg, t_shell *sh, char *sep)
{
	char	*key;
	char	*old_val;
	char	*new_val;

	key = ft_substr(arg, 0, sep - arg);
	old_val = get_env_value(key, sh);
	if (old_val && old_val[0])
		new_val = ft_strjoin(old_val, sep + 2);
	else
		new_val = ft_strdup(sep + 2);
	set_env_var(sh, key, new_val);
	free(key);
	free(new_val);
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

	sys_idx = find_env_var_index(merged_env, key, ft_strlen(key));
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
			if (find_env_var_index(merged_env, key, ft_strlen(key)) >= 0)
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