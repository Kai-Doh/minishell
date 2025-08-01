/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:10:08 by ktiomico          #+#    #+#             */
/*   Updated: 2025/04/29 14:25:01 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_input(char *rl, t_shell *sh);

static int	handle_readline_result(char *line, t_shell *sh)
{
	int	keep_running;

	if (!line)
	{
		if (isatty(STDIN_FILENO))
			ft_putendl_fd("exit", STDOUT_FILENO);
		return (0);
	}
	keep_running = !handle_input(line, sh);
	free(line);
	return (keep_running);
}

static int	shell_iteration(t_shell *sh)
{
	char	*line;
	char	*prompt_str;

	prompt_str = build_prompt();
	if (!prompt_str)
		return (1);
	line = safe_readline(prompt_str);
	free(prompt_str);
	return (handle_readline_result(line, sh));
}

void	start_shell_loop(t_shell *sh)
{
	while (shell_iteration(sh))
		;
}

static int	handle_input(char *rl, t_shell *sh)
{
	t_token	*tokens;
	t_cmd	*cmds;
	int		err;

	tokens = NULL;
	err = 0;
	if (!rl || rl[0] == '\0')
		return (0);
	add_history(rl);
	rl = strip_comments(rl);
	tokens = lexer(rl, &err);
	if (!tokens)
		return (lexer_fail(err, sh));
	sh->all_tokens = tokens;
	cmds = parse(tokens, sh);
	sh->all_cmds = cmds;
	if (!cmds)
	{
		free_tokens(sh->all_tokens);
		sh->all_tokens = NULL;
		sh->all_cmds = NULL;
		cleanup_heredoc_tracking(sh);
		init_heredoc_tracking(sh);
		if (sh->last_exit_status == 2)
			return (0);
		return (0);
	}
	execute(cmds, sh);
	free_tokens(sh->all_tokens);
	free_cmds(sh->all_cmds);
	sh->all_tokens = NULL;
	sh->all_cmds = NULL;
	close_all_heredoc_fds(sh);
	cleanup_heredoc_tracking(sh);
	init_heredoc_tracking(sh);
	if (sh->should_exit)
		return (1);
	return (0);
}

