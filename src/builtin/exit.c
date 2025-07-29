/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:47:00 by ktiomico          #+#    #+#             */
/*   Updated: 2025/04/29 15:47:06 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_long(char *str)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	i = 0;
	if (str[0] == '-' || str[0] == '+')
	{
		i = 1;
		len--;
	}
	if (len > 19)
		return (0);
	if (len == 19)
	{
		if (str[0] == '-' && ft_strncmp(str + i, "9223372036854775808", 19) > 0)
			return (0);
		if (str[0] != '-' && ft_strncmp(str + i, "9223372036854775807", 19) > 0)
			return (0);
	}
	return (1);
}

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (is_valid_long(str));
}

int	ft_exit(char **args, t_shell *sh)
{
	int	code;

	ft_putendl_fd("exit", STDERR_FILENO);
	if (args[1] && !is_numeric(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		ft_free_split(sh->env);
		exit(2);
	}
	if (args[1] && args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	if (args[1])
		code = ft_atoi(args[1]);
	else
		code = sh->last_exit_status;
	ft_free_split(sh->env);
	exit(code);
}
