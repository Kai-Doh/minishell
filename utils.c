/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:21:45 by ktiomico          #+#    #+#             */
/*   Updated: 2025/04/29 14:26:39 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_msg(char *msg, int code, t_shell *sh)
{
	if (msg)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putendl_fd(msg, 2);
	}
	if (sh && sh->env)
		ft_free_split(sh->env);
	exit(code);
}

void	free_tokens(t_token *tok)
{
	t_token	*tmp;

	while (tok)
	{
		tmp = tok->next;
		free(tok->content);
		free(tok);
		tok = tmp;
	}
}

char	**ft_args_add(char **arr, char *new_arg)
{
	char	**new;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (arr && arr[count])
		count++;
	new = malloc(sizeof(char *) * (count + 2));
	if (!new)
		return (NULL);
	while (i < count)
	{
		new[i] = arr[i];
		i++;
	}
	new[count] = new_arg;
	new[count + 1] = NULL;
	free(arr);
	return (new);
}

char    *strip_comments(char *line)
{
        int     i;
        int     in_s;
        int     in_d;

        if (!line)
                return (NULL);
        i = 0;
        in_s = 0;
        in_d = 0;
        while (line[i])
        {
                if (line[i] == '\'' && in_d == 0)
                        in_s = 1 - in_s;
                else if (line[i] == '"' && in_s == 0)
                        in_d = 1 - in_d;
                else if (line[i] == '#' && !in_s && !in_d)
                {
                        line[i] = '\0';
                        break ;
                }
                i++;
        }
        return (line);
}
