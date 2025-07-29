/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:00:00 by ktiomico          #+#    #+#             */
/*   Updated: 2025/07/28 16:00:00 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_entry_to_result(char **result, char *name)
{
	char	*temp;

	if (ft_strlen(*result) > 0)
	{
		temp = ft_strjoin(*result, " ");
		free(*result);
		*result = temp;
	}
	temp = ft_strjoin(*result, name);
	free(*result);
	*result = temp;
}

static char	*expand_single_wildcard(void)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*result;

	result = ft_strdup("");
	dir = opendir(".");
	if (!dir)
		return (result);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.')
			add_entry_to_result(&result, entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
	return (result);
}

char	*expand_wildcards(char *s)
{
	if (!s)
		return (ft_strdup(""));
	if (ft_strncmp(s, "*", 2) == 0)
		return (expand_single_wildcard());
	return (ft_strdup(s));
}
