/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:57:41 by ktiomico          #+#    #+#             */
/*   Updated: 2025/05/26 12:07:43 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_key(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	update_or_add(char *arg, t_shell *sh)
{
	char	*key;
	char	*equal;
	int		i;

	equal = ft_strchr(arg, '=');
	if (!equal)
		return ;
	key = ft_substr(arg, 0, equal - arg);
	if (!key)
		return ;
	i = 0;
	while (sh->env[i])
	{
		if (!ft_strncmp(sh->env[i], key, ft_strlen(key))
			&& sh->env[i][ft_strlen(key)] == '=')
		{
			free(sh->env[i]);
			sh->env[i] = ft_strdup(arg);
			free(key);
			return ;
		}
		i++;
	}
	free(key);
	sh->env = ft_strs_add(sh->env, arg);
}

int	ft_export(char **args, t_shell *sh)
{
	int	i;

	(void)sh;
	if (!args[1])
		return (ft_env(sh->env));
	i = 1;
	while (args[i])
	{
		if (!is_valid_key(args[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			return (1);
		}
		if (ft_strchr(args[i], '='))
			update_or_add(args[i], sh);
		i++;
	}
	return (0);
}
