/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:58:07 by ktiomico          #+#    #+#             */
/*   Updated: 2025/05/26 12:03:12 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **args, char **env)
{
	int		i;
	int		j;

	(void)env;
	i = 1;
	while (args[i])
	{
		j = 0;
		while (g_env[j])
		{
			if (!ft_strncmp(g_env[j], args[i], ft_strlen(args[i]))
				&& g_env[j][ft_strlen(args[i])] == '=')
			{
				g_env = ft_strs_remove(g_env, j);
				break ;
			}
			j++;
		}
		i++;
	}
	return (0);
}
