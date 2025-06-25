<<<<<<< HEAD
#include "minishell.h"

static char *strip_quotes(char *str)
{
    size_t len;

    if (!str)
        return (NULL);
    len = ft_strlen(str);
    if (len >= 2 && ((str[0] == '\'' && str[len - 1] == '\'') ||
        (str[0] == '"' && str[len - 1] == '"')))
        return (ft_substr(str, 1, len - 2));
    return (ft_strdup(str));
}

void    builtin_echo(char *arg)
{
    char *output;

    if (!arg)
    {
        printf("\n");
        return ;
    }
    output = strip_quotes(arg);
    if (output)
    {
        printf("%s\n", output);
        free(output);
    }
    else
        printf("%s\n", arg);
}

=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:42:53 by ktiomico          #+#    #+#             */
/*   Updated: 2025/04/29 15:43:13 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (args[i] && !ft_strncmp(args[i], "-n", 3))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
>>>>>>> karl
