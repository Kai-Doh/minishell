/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github <github@kaidoh.ch>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 23:23:45 by github            #+#    #+#             */
/*   Updated: 2025/06/24 23:23:49 by github           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	if (c == ' ')
		return (1);
	if (c >= 9 && c <= 13)
		return (1);
	return (0);
}

int	is_special(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

void	quote_error(int in_s)
{
	ft_putstr_fd("minishell: unexpected EOF while looking for matching '", 2);
	if (in_s)
		ft_putchar_fd('\'', 2);
	else
		ft_putchar_fd('"', 2);
	ft_putendl_fd("'", 2);
	g_lexer_error = 1;
}
