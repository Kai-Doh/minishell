/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:10:21 by ktiomico          #+#    #+#             */
/*   Updated: 2025/04/17 13:49:01 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ───────── CHILD ───────── */
static int	spawn_child(char **argv, int in_fd, int out_fd, char **env)
{
	pid_t	pid;
	char	*path;

	path = find_cmd_path(argv[0], env);
	if (!path)
	{
		printf("minishell: %s: command not found\n", argv[0]);
		return (0);
	}
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		if (out_fd != STDOUT_FILENO)
			dup2(out_fd, STDOUT_FILENO);
		if (in_fd != STDIN_FILENO)
			dup2(in_fd, STDIN_FILENO);
		execve(path, argv, env);
		perror(path);
		exit(EXIT_FAILURE);
	}
	free(path);
	return (0);
}


static void	update_parent(int *in_fd, int fds[2], int has_pipe)
{
	if (*in_fd != STDIN_FILENO)
		close(*in_fd);
	if (has_pipe)
	{
		close(fds[1]);
		*in_fd = fds[0];
	}
}

static int	process_cmd(t_token **tok, int *in_fd, char **env)
{
	int		fds[2];
	int		has_pipe;
	char	**argv;
	t_token	*next;
	int		out_fd;

	argv = tok_to_argv(*tok, &has_pipe, &next);
	if (!argv || !argv[0])
		return (1);
	if (has_pipe)
	{
		if (pipe(fds) < 0)
			return (perror("pipe"), 1);
		out_fd = fds[1];
	}
	else
		out_fd = STDOUT_FILENO;
	if (spawn_child(argv, *in_fd, out_fd, env))
		return (1);
	update_parent(in_fd, fds, has_pipe);
	free(argv);
	*tok = next;
	return (0);
}

/* ───────── DRIVER ──────── */
int	exec_pipeline(t_token *tok, char **env)
{
	int	in_fd;

	in_fd = STDIN_FILENO;
	while (tok)
	{
		if (process_cmd(&tok, &in_fd, env))
			return (1);
	}
	while (wait(NULL) > 0)
		;
	return (0);
}
