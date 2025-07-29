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

static void	update_env_var(t_shell *sh, const char *key, const char *val)
{
	set_env_var(sh, key, val);
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
	update_env_var(sh, "OLDPWD", old);
	update_env_var(sh, "PWD", cwd);
}
