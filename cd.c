/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thofstet <thofstet>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:15:41 by thofstet          #+#    #+#             */
/*   Updated: 2025/05/10 17:16:58 by thofstet         ###   ########.fr       */
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
	if (!args[1] || ft_strncmp(args[1], "~", 2) == 0)
	{
		char	*home;
		home = getenv("HOME");
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
		char	*old;
		
		old = getenv("OLDPWD");
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
