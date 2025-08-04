/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:30:00 by ktiomico          #+#    #+#             */
/*   Updated: 2025/07/28 16:30:00 by ktiomico         ###   ########.fr       */
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

static void	set_shlvl_value(t_shell *sh, int shlvl_idx, char *new_entry)
{
	char	**new_env;

	if (shlvl_idx >= 0)
	{
		free(sh->env[shlvl_idx]);
		sh->env[shlvl_idx] = new_entry;
	}
	else
	{
		new_env = ft_strs_add(sh->env, new_entry);
		free(new_entry);
		if (new_env)
			sh->env = new_env;
	}
}

void	increment_shlvl(t_shell *sh)
{
	int		shlvl_idx;
	int		current_shlvl;
	char	*new_shlvl_str;
	char	*new_entry;

	shlvl_idx = find_env_var(sh->env, "SHLVL");
	if (shlvl_idx >= 0)
	{
		current_shlvl = ft_atoi(sh->env[shlvl_idx] + 6);
		current_shlvl++;
	}
	else
		current_shlvl = 1;
	new_shlvl_str = ft_itoa(current_shlvl);
	if (!new_shlvl_str)
		return ;
	new_entry = ft_strjoin("SHLVL=", new_shlvl_str);
	free(new_shlvl_str);
	if (!new_entry)
		return ;
	set_shlvl_value(sh, shlvl_idx, new_entry);
}
