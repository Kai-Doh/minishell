/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 00:00:00 by ktiomico          #+#    #+#             */
/*   Updated: 2025/08/01 00:00:01 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
