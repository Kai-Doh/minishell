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

int	handle_redir(t_redir *r)
{
	while (r)
	{
		if (r->type == REDIR_IN)
		{
			if (do_redir_in(r) != 0)
				return (1);
		}
		else if (r->type == REDIR_OUT)
		{
			if (do_redir_out(r) != 0)
				return (1);
		}
		else if (r->type == APPEND)
		{
			if (do_redir_append(r) != 0)
				return (1);
		}
		else if (r->type == HEREDOC)
			do_heredoc(r);
		r = r->next;
	}
	return (0);
}

int	do_redir_in(t_redir *r)
{
	int	fd;

	fd = open(r->file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(r->file, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	do_redir_out(t_redir *r)
{
	int	fd;

	fd = open(r->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(r->file, 2);
		ft_putendl_fd(": Cannot open output file", 2);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	do_redir_append(t_redir *r)
{
	int	fd;

	fd = open(r->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(r->file, 2);
		ft_putendl_fd(": Cannot append to file", 2);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

void	do_heredoc(t_redir *r)
{
	if (r->heredoc_fd >= 0)
	{
		fcntl(r->heredoc_fd, F_SETFD, 0);
		dup2(r->heredoc_fd, STDIN_FILENO);
		close(r->heredoc_fd);
		r->heredoc_fd = -1;
	}
}
