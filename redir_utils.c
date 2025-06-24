/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:01:08 by ktiomico          #+#    #+#             */
/*   Updated: 2025/04/29 14:19:54 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    handle_redir(t_redir *r)
{
    while (r)
    {
        if (r->type == REDIR_IN)
            do_redir_in(r);
        else if (r->type == REDIR_OUT)
            do_redir_out(r);
        else if (r->type == APPEND)
            do_redir_append(r);
        else if (r->type == HEREDOC)
            do_heredoc(r);
        r = r->next;
    }
}

void    do_redir_in(t_redir *r)
{
    int    fd;

    fd = open(r->file, O_RDONLY);
    if (fd < 0)
        exit_msg("No such file or permission denied", 1, NULL);
    dup2(fd, STDIN_FILENO);
    close(fd);
}

void    do_redir_out(t_redir *r)
{
    int    fd;

    fd = open(r->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0)
        exit_msg("Cannot open output file", 1, NULL);
    dup2(fd, STDOUT_FILENO);
    close(fd);
}

void    do_redir_append(t_redir *r)
{
    int    fd;

    fd = open(r->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd < 0)
        exit_msg("Cannot append to file", 1, NULL);
    dup2(fd, STDOUT_FILENO);
    close(fd);
}

void    do_heredoc(t_redir *r)
{
    int    fd;

    fd = create_heredoc(r->file);
    if (fd >= 0)
        dup2(fd, STDIN_FILENO);
}
