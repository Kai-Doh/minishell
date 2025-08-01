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
	int		is_interactive;
	int		len;

	is_interactive = isatty(STDIN_FILENO);
	len = ft_strlen(delimiter);
	while (1)
	{
		if (is_interactive)
			line = readline("> ");
		else
			line = read_line_direct();
		if (!line)
			break ;
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

static void	heredoc_child(char *delimiter, int write_fd, t_shell *sh)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	write_to_pipe(write_fd, delimiter);
	close(write_fd);
	if (sh->all_tokens)
		free_tokens(sh->all_tokens);
	if (sh->all_cmds)
		free_cmds(sh->all_cmds);
	if (sh->env)
		ft_free_split(sh->env);
	sh->env = NULL;
	sh->all_tokens = NULL;
	sh->all_cmds = NULL;
	cleanup_heredoc_tracking(sh);
	cleanup_all_fds();
	exit(0);
}

static pid_t	fork_heredoc(char *delimiter, int fd[2], t_shell *sh)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		heredoc_child(delimiter, fd[1], sh);
	return (pid);
}

int	create_heredoc(char *delimiter, t_shell *sh)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (!delimiter || *delimiter == '\0')
		return (-1);
	if (pipe(fd) == -1)
		return (-1);
	pid = fork_heredoc(delimiter, fd, sh);
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
