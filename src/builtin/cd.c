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

static int	handle_home_dir(char **target)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
	{
		ft_putendl_fd("cd: HOME not set", 2);
		return (1);
	}
	*target = home;
	return (0);
}

static int	handle_oldpwd_dir(char **target, t_shell *sh)
{
	char	*oldpwd;

	oldpwd = get_env_value("OLDPWD", sh);
	if (!oldpwd || !*oldpwd)
	{
		ft_putendl_fd("cd: OLDPWD not set", 2);
		return (1);
	}
	*target = oldpwd;
	printf("%s\n", oldpwd);
	return (0);
}

static int	get_target_dir(char **args, char **target, t_shell *sh)
{
	*target = NULL;
	if (!args[1])
		return (handle_home_dir(target));
	else if (ft_strncmp(args[1], "-", 2) == 0)
		return (handle_oldpwd_dir(target, sh));
	else
		*target = args[1];
	return (0);
}

int	ft_cd(char **args, t_shell *sh)
{
	char	*target;
	char	cwd[4096];
	char	old[4096];
	int		ret;

	target = NULL;
	ret = cd_validate_args(args);
	if (ret != 0)
		return (ret);
	if (getcwd(old, sizeof(old)) == NULL)
		old[0] = '\0';
	if (get_target_dir(args, &target, sh) != 0)
		return (1);
	if (chdir(target) != 0)
	{
		perror("cd");
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)))
		update_pwd_vars(sh, old, cwd);
	return (0);
}
