/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 00:00:00 by ktiomico          #+#    #+#             */
/*   Updated: 2025/07/31 00:00:00 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(const char *cmd, const char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd((char *)cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd((char *)msg, 2);
}

void	print_command_error(const char *cmd, const char *arg, const char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd((char *)cmd, 2);
	ft_putstr_fd(": ", 2);
	if (arg)
	{
		ft_putstr_fd((char *)arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd((char *)msg, 2);
}

void	print_syntax_error(const char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	if (token)
		ft_putstr_fd((char *)token, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putchar_fd('\n', 2);
}