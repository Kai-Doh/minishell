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

static int      find_env_index(char **env, const char *key)
{
    int i;

    i = 0;
    while (env && env[i])
    {
        if (!ft_strncmp(env[i], key, ft_strlen(key))
            && env[i][ft_strlen(key)] == '=')
            return (i);
        i++;
    }
    return (-1);
}

static void     update_env_var(t_shell *sh, const char *key, const char *val)
{
    char    *tmp;
    char    *entry;
    int             idx;

    tmp = ft_strjoin(key, "=");
    if (!tmp)
        return ;
    entry = ft_strjoin(tmp, val);
    free(tmp);
    if (!entry)
        return ;
    idx = find_env_index(sh->env, key);
    if (idx >= 0)
    {
        free(sh->env[idx]);
        sh->env[idx] = ft_strdup(entry);
        free(entry);
    }
    else
        sh->env = ft_strs_add(sh->env, entry);
}

int     ft_cd(char **args, t_shell *sh)
{
    char    *target;
    char    cwd[4096];
    char    old[4096];

    if (args[1] && args[2])
    {
        ft_putendl_fd("cd: too many arguments", 2);
        return (1);
    }
    if (getcwd(old, sizeof(old)) == NULL)
        old[0] = '\0';
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
        update_env_var(sh, "OLDPWD", old);
        update_env_var(sh, "PWD", cwd);
    }
    return (0);
}
