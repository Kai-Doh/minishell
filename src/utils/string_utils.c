/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github <github@kaidoh.ch>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 23:50:00 by github            #+#    #+#             */
/*   Updated: 2025/06/24 23:50:02 by github           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_str(char *base, const char *add)
{
	char	*tmp;

	tmp = ft_strjoin(base, add);
	free(base);
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	*append_char(char *base, char c)
{
	char	str[2];

	str[0] = c;
	str[1] = '\0';
	return (append_str(base, str));
}
