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

int	ft_unset(char **args, t_shell *sh)
{
	int		i;
	int		j;
	char	**new_env;

	i = 1;
	while (args[i])
	{
		j = 0;
		while (sh->env[j])
		{
			if (!ft_strncmp(sh->env[j], args[i], ft_strlen(args[i]))
				&& sh->env[j][ft_strlen(args[i])] == '=')
			{
				new_env = ft_strs_remove(sh->env, j);
				if (new_env)
					sh->env = new_env;
				break ;
			}
			j++;
		}
		i++;
	}
	return (0);
}
