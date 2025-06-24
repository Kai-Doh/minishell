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


static t_redir  *add_redir(t_token **tok, t_shell *sh)
{
    t_redir    *r;

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

static void     process_word(t_cmd *cmd, t_token **tok, t_shell *sh)
{
    char    *arg;

    arg = expand_word((*tok)->content, sh);
    cmd->args = ft_args_add(cmd->args, arg);
    *tok = (*tok)->next;
}

static void     process_redir(t_cmd *cmd, t_redir **last,
                        t_token **tok, t_shell *sh)
{
    t_redir *r;

    r = add_redir(tok, sh);
    if (!cmd->redir)
        cmd->redir = r;
    else
        (*last)->next = r;
    *last = r;
}

static t_cmd    *add_command(t_token **tok, t_shell *sh)
{
    t_cmd   *cmd;
    t_redir *last;

    cmd = malloc(sizeof(t_cmd));
    cmd->args = NULL;
    cmd->redir = NULL;
    cmd->next = NULL;
    last = NULL;
    while (*tok && (*tok)->type != PIPE)
    {
        if ((*tok)->type == WORD)
            process_word(cmd, tok, sh);
        else if ((*tok)->type >= REDIR_IN && (*tok)->type <= APPEND)
            process_redir(cmd, &last, tok, sh);
        else
            *tok = (*tok)->next;
    }
    if (*tok && (*tok)->type == PIPE)
        *tok = (*tok)->next;
    return (cmd);
}

t_cmd   *parse(t_token *tok, t_shell *sh)
{
    t_cmd    *first;
    t_cmd    *last;
    t_cmd    *new;

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
