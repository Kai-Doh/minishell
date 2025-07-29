/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:00:00 by ktiomico          #+#    #+#             */
/*   Updated: 2025/07/28 16:00:00 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_env_var(t_shell *sh, const char *key, size_t key_len)
{
	int	i;

	i = 0;
	while (sh->env && sh->env[i])
	{
		if (!ft_strncmp(sh->env[i], key, key_len)
			&& sh->env[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
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
	idx = find_env_var(sh, key, key_len);
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
