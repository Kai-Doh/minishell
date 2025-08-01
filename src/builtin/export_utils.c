/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 00:00:00 by ktiomico          #+#    #+#             */
/*   Updated: 2025/08/01 00:00:01 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_var_with_value(char *env_var, char *eq_pos)
{
	write(STDOUT_FILENO, env_var, eq_pos - env_var);
	if (eq_pos[1] != '\0')
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(eq_pos + 1, STDOUT_FILENO);
		ft_putendl_fd("\"", STDOUT_FILENO);
	}
	else
	{
		ft_putendl_fd("", STDOUT_FILENO);
	}
}

static void	print_var_without_value(char *env_var)
{
	ft_putstr_fd(env_var, STDOUT_FILENO);
	ft_putendl_fd("", STDOUT_FILENO);
}

void	print_export_format(t_shell *sh)
{
	int		i;
	char	*eq_pos;

	i = 0;
	while (sh->env[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		eq_pos = ft_strchr(sh->env[i], '=');
		if (eq_pos)
			print_var_with_value(sh->env[i], eq_pos);
		else
			print_var_without_value(sh->env[i]);
		i++;
	}
}

int	variable_exists(char *var, t_shell *sh)
{
	int		i;
	size_t	len;

	len = ft_strlen(var);
	i = 0;
	while (sh->env[i])
	{
		if (!ft_strncmp(sh->env[i], var, len)
			&& (sh->env[i][len] == '=' || sh->env[i][len] == '\0'))
			return (1);
		i++;
	}
	return (0);
}

void	export_variable_without_value(char *var, t_shell *sh)
{
	char	**new_env;

	if (variable_exists(var, sh))
		return ;
	new_env = ft_strs_add(sh->env, var);
	if (!new_env)
		return ;
	sh->env = new_env;
}
