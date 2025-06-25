/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:59:21 by ktiomico          #+#    #+#             */
/*   Updated: 2025/04/29 15:30:48 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_to_pipe(int fd, char *delimiter)
{
	char	*line;
	int		len;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		len = ft_strlen(delimiter);
		if (ft_strncmp(line, delimiter, len) == 0
			&& ft_strlen(line) == (size_t)len)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

static void	heredoc_child(char *delimiter, int write_fd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	write_to_pipe(write_fd, delimiter);
	close(write_fd);
	exit(0);
}

static pid_t	fork_heredoc(char *delimiter, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		heredoc_child(delimiter, fd[1]);
	return (pid);
}

int	create_heredoc(char *delimiter)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (!delimiter || *delimiter == '\0')
		return (-1);
	if (pipe(fd) == -1)
		return (-1);
	pid = fork_heredoc(delimiter, fd);
	if (pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(fd[0]);
		return (-1);
	}
	return (fd[0]);
}
