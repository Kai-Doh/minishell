/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 00:00:00 by ktiomico          #+#    #+#             */
/*   Updated: 2025/07/31 00:00:01 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_heredoc_fd(t_shell *sh, int fd)
{
	int	*new_fds;
	int	i;

	new_fds = malloc(sizeof(int) * (sh->heredoc_count + 1));
	if (!new_fds)
		return ;
	i = 0;
	while (i < sh->heredoc_count)
	{
		new_fds[i] = sh->heredoc_fds[i];
		i++;
	}
	new_fds[sh->heredoc_count] = fd;
	free(sh->heredoc_fds);
	sh->heredoc_fds = new_fds;
	sh->heredoc_count++;
}

void	close_all_heredoc_fds(t_shell *sh)
{
	int	i;

	i = 0;
	while (i < sh->heredoc_count)
	{
		if (sh->heredoc_fds[i] >= 0)
		{
			close(sh->heredoc_fds[i]);
			sh->heredoc_fds[i] = -1;
		}
		i++;
	}
}

void	close_unused_global_heredocs(t_shell *sh, t_redir *keep_redir)
{
	int		i;
	t_redir	*redir;
	int		keep_fd;

	i = 0;
	while (i < sh->heredoc_count)
	{
		keep_fd = 0;
		redir = keep_redir;
		while (redir)
		{
			if (redir->type == HEREDOC
				&& redir->heredoc_fd == sh->heredoc_fds[i])
			{
				keep_fd = 1;
				break ;
			}
			redir = redir->next;
		}
		if (!keep_fd && sh->heredoc_fds[i] >= 0)
		{
			close(sh->heredoc_fds[i]);
			sh->heredoc_fds[i] = -1;
		}
		i++;
	}
}

void	mark_heredoc_closed(t_shell *sh, int fd)
{
	int	i;

	i = 0;
	while (i < sh->heredoc_count)
	{
		if (sh->heredoc_fds[i] == fd)
		{
			sh->heredoc_fds[i] = -1;
			return ;
		}
		i++;
	}
}

void	cleanup_heredoc_tracking(t_shell *sh)
{
	free(sh->heredoc_fds);
	sh->heredoc_fds = NULL;
	sh->heredoc_count = 0;
}

