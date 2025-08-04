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

char	**dup_env(char **env)
{
	int		i;
	char	**new;

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
		if (!new[i])
		{
			ft_free_split(new);
			return (NULL);
		}
		i++;
	}
	new[i] = NULL;
	return (new);
}

static void	free_partial(char **arr, int n)
{
	while (n-- > 0)
		free(arr[n]);
	free(arr);
}

static int	copy_except(char **src, char **dst, int idx)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (i != idx)
		{
			dst[j] = ft_strdup(src[i]);
			if (!dst[j])
				return (free_partial(dst, j), 0);
			j++;
		}
		i++;
	}
	dst[j] = NULL;
	return (1);
}

char	**ft_strs_add(char **env, char *new_entry)
{
	char	**new;
	int		len;
	int		i;

	len = 0;
	while (env && env[len])
		len++;
	new = malloc(sizeof(char *) * (len + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new[i] = ft_strdup(env[i]);
		if (!new[i])
			return (free_partial(new, i), NULL);
		i++;
	}
	new[i] = ft_strdup(new_entry);
	if (!new[i])
		return (free_partial(new, i), NULL);
	new[i + 1] = NULL;
	ft_free_split(env);
	return (new);
}

char	**ft_strs_remove(char **env, int index)
{
	char	**new;
	int		len;

	len = 0;
	while (env && env[len])
		len++;
	new = malloc(sizeof(char *) * len);
	if (!new)
		return (NULL);
	if (!copy_except(env, new, index))
		return (NULL);
	ft_free_split(env);
	return (new);
}
