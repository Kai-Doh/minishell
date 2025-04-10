/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:10:08 by ktiomico          #+#    #+#             */
/*   Updated: 2025/04/10 18:19:26 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prompt(void)
{
	char	*username;
	char	*start;
	char	*end;
	char	*full;
	int		len;

	username = getenv("USER");
	if (!username)
		username = "unknown";
	start = GREEN "👾 Minishell" YELLOW "@";
	end = GREEN " ➜ " RESET;
	len = ft_strlen(start) + ft_strlen(username) + ft_strlen(end) + 1;
	full = malloc(len);
	if (!full)
		return (NULL);
	ft_strlcpy(full, start, len);
	ft_strlcat(full, username, len);
	ft_strlcat(full, end, len);
	return (full);
}
