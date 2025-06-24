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
extern char **g_env;

void	exit_msg(char *msg, int code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd(msg, 2);
        if (g_env)
                ft_free_split(g_env);
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

void	free_cmds(t_cmd *cmd)
{
	t_cmd		*tmp;
	t_redir		*r;
	t_redir		*r_next;
	int			i;

	while (cmd)
	{
		tmp = cmd->next;
		i = 0;
		while (cmd->args && cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
		r = cmd->redir;
		while (r)
		{
			r_next = r->next;
			free(r->file);
			free(r);
			r = r_next;
		}
                free(cmd);
                cmd = tmp;
        }
}

char    *remove_quotes(char *s)
{
        char    *res;
        int             i;
        int             j;

        i = 0;
        j = 0;
        while (s && s[i])
        {
                if (s[i] != '\'' && s[i] != '"')
                        j++;
                i++;
        }
        res = malloc(j + 1);
        if (!res)
                return (NULL);
        i = 0;
        j = 0;
        while (s && s[i])
        {
                if (s[i] != '\'' && s[i] != '"')
                        res[j++] = s[i];
                i++;
        }
        res[j] = '\0';
        return (res);
}
