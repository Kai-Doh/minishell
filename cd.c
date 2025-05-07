/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thofstet <thofstet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:48:42 by thofstet          #+#    #+#             */
/*   Updated: 2025/05/07 17:48:42 by thofstet         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **args, char ***envp)
{
	char	cwd[4096];
	char	*target;
	char	*oldpwd;

	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("cd: getcwd");
		return (1);
	}
	oldpwd = ft_strdup(cwd);
	if (!oldpwd)
		return (1);

	// Détermination sécurisée de la cible
	if (!args[1] || ft_strncmp(args[1], "~", 2) == 0)
	{
		char *home = getenv("HOME");
		if (!home)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			free(oldpwd);
			return (1);
		}
		target = ft_strdup(home);
		if (!target)
		{
			ft_putendl_fd("cd: memory allocation failed", 2);
			free(oldpwd);
			return (1);
		}
	}
	else if (ft_strncmp(args[1], "-", 2) == 0)
	{
		char *old = getenv("OLDPWD");
		if (!old)
		{
			ft_putendl_fd("cd: OLDPWD not set", 2);
			free(oldpwd);
			return (1);
		}
		target = ft_strdup(old);
		if (!target)
		{
			ft_putendl_fd("cd: memory allocation failed", 2);
			free(oldpwd);
			return (1);
		}
	}
	else
	{
		target = ft_strdup(args[1]);
		if (!target)
		{
			ft_putendl_fd("cd: memory allocation failed", 2);
			free(oldpwd);
			return (1);
		}
	}

	if (chdir(target) != 0)
	{
		perror("cd");
		free(oldpwd);
		free(target);
		return (1);
	}

	update_env_var(envp, "OLDPWD", oldpwd);
	if (getcwd(cwd, sizeof(cwd)))
		update_env_var(envp, "PWD", cwd);

	if (args[1] && ft_strncmp(args[1], "-", 2) == 0)
		printf("%s\n", cwd);

	free(oldpwd);
	free(target);
	return (0);
}
