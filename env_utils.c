/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:56:49 by ktiomico          #+#    #+#             */
/*   Updated: 2025/05/26 12:00:58 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **dup_env(char **env)
{
    int        i;
    char    **new;

    i = 0;
    while (env[i])
        i++;
    new = malloc(sizeof(char *) * (i + 1));
    if (!new)
        return (NULL);
    i = 0;
    while (env[i])
    {
        new[i] = ft_strdup(env[i]);
        i++;
    }
    new[i] = NULL;
    return (new);
}

int    ft_env(char **env)
{
    int    i;
     
    i = 0;
    while (env && env[i])
    {
        if (ft_strchr(env[i], '='))
            ft_putendl_fd(env[i], STDOUT_FILENO);
        i++;
    }
    return (0);
}

char    **ft_strs_add(char **env, char *new_entry)
{
    int        i;
    char    **new;

    i = 0;
    while (env && env[i])
        i++;
    new = malloc(sizeof(char *) * (i + 2));
    if (!new)
        return (NULL);
    i = 0;
    while (env && env[i])
    {
        new[i] = ft_strdup(env[i]);
        i++;
    }
    new[i] = ft_strdup(new_entry);
    new[i + 1] = NULL;
    ft_free_split(env);
    return (new);
}

char    **ft_strs_remove(char **env, int index)
{
    int        i;
    int        j;
    char    **new;

    i = 0;
    while (env && env[i])
        i++;
    new = malloc(sizeof(char *) * i);
    if (!new)
        return (NULL);
    i = 0;
    j = 0;
    while (env[i])
    {
        if (i != index)
            new[j++] = ft_strdup(env[i]);
        i++;
    }
    new[j] = NULL;
    ft_free_split(env);
    return (new);
}

