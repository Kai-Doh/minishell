/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:00:00 by ktiomico          #+#    #+#             */
/*   Updated: 2025/07/28 16:00:00 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_env_var_if_exists(t_shell *sh, const char *key,
		const char *val)
{
	int		i;
	size_t	key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (sh->env && sh->env[i])
	{
		if (!ft_strncmp(sh->env[i], key, key_len)
			&& sh->env[i][key_len] == '=')
		{
			set_env_var(sh, key, val);
			return ;
		}
		i++;
	}
}

int	cd_validate_args(char **args)
{
	if (args[1] && args[2])
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (2);
	}
	return (0);
}

void	update_pwd_vars(t_shell *sh, char *old, char *cwd)
{
	update_env_var_if_exists(sh, "OLDPWD", old);
	update_env_var_if_exists(sh, "PWD", cwd);
}
