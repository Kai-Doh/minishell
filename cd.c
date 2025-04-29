/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:40:39 by ktiomico          #+#    #+#             */
/*   Updated: 2025/04/29 15:40:55 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **args, char **env)
{
	char	*target;
	char	cwd[4096];

	if (!args[1])
	{
		target = getenv("HOME");
		if (!target)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			return (1);
		}
	}
	else
		target = args[1];
	if (chdir(target) != 0)
	{
		perror("cd");
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)))
	{
		(void)env;
	}
	return (0);
}
