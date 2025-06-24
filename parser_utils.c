/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github <github@kaidoh.ch>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 23:39:02 by github            #+#    #+#             */
/*   Updated: 2025/06/24 23:39:04 by github           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_str(char *base, const char *add)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strjoin(base, add);
	free(base);
	return (tmp);
}

char	*append_char(char *base, char c)
{
	char	str[2];

	str[0] = c;
	str[1] = '\0';
	return (append_str(base, str));
}

char	*get_env_value(char *name, t_shell *sh)
{
	int		i;
	size_t	len;

	i = 0;
	len = 0;
	if (!name)
		return ("");
	len = ft_strlen(name);
	while (sh->env && sh->env[i])
	{
		if (!ft_strncmp(sh->env[i], name, len)
			&& sh->env[i][len] == '=')
			return (sh->env[i] + len + 1);
		i++;
	}
	return ("");
}
