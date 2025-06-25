/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github <github@kaidoh.ch>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 00:00:48 by github            #+#    #+#             */
/*   Updated: 2025/06/25 00:00:59 by github           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_unquoted_chars(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s && s[i])
	{
		if (s[i] != '\'' && s[i] != '"')
			count++;
		i++;
	}
	return (count);
}

char	*remove_quotes(char *s)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = NULL;
	res = malloc(count_unquoted_chars(s) + 1);
	if (!res)
		return (NULL);
	while (s && s[i])
	{
		if (s[i] != '\'' && s[i] != '"')
		{
			res[j] = s[i];
			j++;
		}
		i++;
	}
	res[j] = '\0';
	return (res);
}
