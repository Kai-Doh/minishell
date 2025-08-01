/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_extract.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 00:00:00 by ktiomico          #+#    #+#             */
/*   Updated: 2025/08/01 00:00:01 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_key(char *env_entry)
{
	char	*equal;

	equal = ft_strchr(env_entry, '=');
	if (!equal)
	{
		return (NULL);
	}
	return (ft_substr(env_entry, 0, equal - env_entry));
}
