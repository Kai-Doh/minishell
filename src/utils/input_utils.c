/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:45:00 by ktiomico          #+#    #+#             */
/*   Updated: 2025/07/28 16:45:00 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_line_direct(void)
{
	char	*line;
	char	*tmp;
	char	c;
	int		i;
	int		size;

	line = malloc((size = 100));
	if (!line)
		return (NULL);
	i = 0;
	while (read(STDIN_FILENO, &c, 1) > 0 && c != '\n')
	{
		if (i >= size - 1)
		{
			tmp = malloc((size *= 2));
			if (!tmp)
				return (free(line), NULL);
			ft_memcpy(tmp, line, i);
			free(line);
			line = tmp;
		}
		line[i++] = c;
	}
	line[i] = '\0';
	return (line);
}
