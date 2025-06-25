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

static void	update_existing_var(t_shell *sh, const char *key, char *entry)
{
	int		i;
	size_t	key_len;
	char	**new_env;

	i = 0;
	key_len = ft_strlen(key);
	while (sh->env && sh->env[i])
	{
		if (!ft_strncmp(sh->env[i], key, key_len)
			&& sh->env[i][key_len] == '=')
		{
			free(sh->env[i]);
			sh->env[i] = ft_strdup(entry);
			free(entry);
			return ;
		}
		i++;
	}
	new_env = ft_strs_add(sh->env, entry);
	if (new_env)
		sh->env = new_env;
	free(entry);
}

static void	update_env_var(t_shell *sh, const char *key, const char *val)
{
	char	*tmp;
	char	*entry;

	tmp = NULL;
	entry = NULL;
	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return ;
	entry = ft_strjoin(tmp, val);
	free(tmp);
	if (!entry)
		return ;
	update_existing_var(sh, key, entry);
}

static int	get_target_dir(char **args, char **target)
{
	char	*home;

	*target = NULL;
	if (!args[1])
	{
		home = getenv("HOME");
		if (!home)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			return (1);
		}
		*target = home;
	}
	else
		*target = args[1];
	return (0);
}

int	ft_cd(char **args, t_shell *sh)
{
	char	*target;
	char	cwd[4096];
	char	old[4096];

	target = NULL;
	if (args[1] && args[2])
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (1);
	}
	if (getcwd(old, sizeof(old)) == NULL)
		old[0] = '\0';
	if (get_target_dir(args, &target) != 0)
		return (1);
	if (chdir(target) != 0)
	{
		perror("cd");
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)))
	{
		update_env_var(sh, "OLDPWD", old);
		update_env_var(sh, "PWD", cwd);
	}
	return (0);
}
