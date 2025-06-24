/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:58:00 by ktiomico          #+#    #+#             */
/*   Updated: 2025/04/29 14:16:30 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char     *get_env_value(char *name, t_shell *sh)
{
        int             i;
        size_t  len;

        if (!name)
                return ("");
        len = ft_strlen(name);
        i = 0;
        while (sh->env && sh->env[i])
        {
                if (!ft_strncmp(sh->env[i], name, len) && sh->env[i][len] == '=')
                        return (sh->env[i] + len + 1);
                i++;
        }
        return ("");
}

static char     *append_str(char *base, const char *add)
{
        char    *tmp;

        tmp = ft_strjoin(base, add);
        free(base);
        return (tmp);
}

static char     *append_char(char *base, char c)
{
        char    str[2];

        str[0] = c;
        str[1] = '\0';
        return (append_str(base, str));
}

static char     *expand_word(char *s, t_shell *sh)
{
        char    *res;
        size_t  i;
        int             in_s;
        int             in_d;

        res = ft_strdup("");
        i = 0;
        in_s = 0;
        in_d = 0;
        while (s && s[i])
        {
                if (s[i] == '\'' && !in_d)
                {
                        in_s = !in_s;
                        i++;
                        continue ;
                }
                if (s[i] == '"' && !in_s)
                {
                        in_d = !in_d;
                        i++;
                        continue ;
                }
                if (s[i] == '$' && !in_s)
                {
                        if (s[i + 1] == '?')
                        {
                                char *tmp = ft_itoa(sh->last_exit_status);
                                res = append_str(res, tmp);
                                free(tmp);
                                i += 2;
                                continue ;
                        }
                        else if (ft_isalpha(s[i + 1]) || s[i + 1] == '_')
                        {
                                size_t start = ++i;
                                while (ft_isalnum(s[i]) || s[i] == '_')
                                        i++;
                                char *name = ft_substr(s, start, i - start);
                                res = append_str(res, get_env_value(name, sh));
                                free(name);
                                continue ;
                        }
                }
                res = append_char(res, s[i]);
                i++;
        }
        return (res);
}


static t_redir  *add_redir(t_token **tok, t_shell *sh)
{
	t_redir	*r;

	r = malloc(sizeof(t_redir));
	if (!r)
		return (NULL);
	r->type = (*tok)->type;
	*tok = (*tok)->next;
	if (!*tok)
		return (NULL);
        r->file = expand_word((*tok)->content, sh);
	r->next = NULL;
	*tok = (*tok)->next;
	return (r);
}

static t_cmd    *add_command(t_token **tok, t_shell *sh)
{
        t_cmd   *cmd;
        t_redir *r;
        t_redir *last;

        cmd = malloc(sizeof(t_cmd));
        cmd->args = NULL;
        cmd->redir = NULL;
        cmd->next = NULL;
        last = NULL;
        while (*tok && (*tok)->type != PIPE)
        {
                if ((*tok)->type == WORD)
                {
                        char *arg = expand_word((*tok)->content, sh);
                        cmd->args = ft_args_add(cmd->args, arg);
                        *tok = (*tok)->next;
                }
                else if ((*tok)->type >= REDIR_IN && (*tok)->type <= APPEND)
                {
                        r = add_redir(tok, sh);
                        if (!cmd->redir)
                                cmd->redir = r;
                        else
                                last->next = r;
                        last = r;
                }
                else
                        *tok = (*tok)->next;
        }
        if (*tok && (*tok)->type == PIPE)
                *tok = (*tok)->next;
        return (cmd);
}

t_cmd   *parse(t_token *tok, t_shell *sh)
{
	t_cmd	*first;
	t_cmd	*last;
	t_cmd	*new;

	first = NULL;
	last = NULL;
	while (tok)
	{
		new = add_command(&tok, sh);
		if (!first)
			first = new;
		else
			last->next = new;
		last = new;
	}
	return (first);
}
