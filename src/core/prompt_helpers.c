/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 00:00:00 by ktiomico          #+#    #+#             */
/*   Updated: 2025/08/01 00:00:01 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_parsing(char *rl, t_shell *sh, t_token **tokens)
{
	int	err;

	err = 0;
	if (!rl || rl[0] == '\0')
		return (0);
	add_history(rl);
	rl = strip_comments(rl);
	*tokens = lexer(rl, &err);
	if (!*tokens)
		return (lexer_fail(err, sh));
	return (-1);
}

void	cleanup_failed_parsing(t_shell *sh)
{
	free_tokens(sh->all_tokens);
	sh->all_tokens = NULL;
	sh->all_cmds = NULL;
	cleanup_heredoc_tracking(sh);
	init_heredoc_tracking(sh);
}

void	cleanup_after_command(t_shell *sh)
{
	free_tokens(sh->all_tokens);
	free_cmds(sh->all_cmds);
	sh->all_tokens = NULL;
	sh->all_cmds = NULL;
	close_all_heredoc_fds(sh);
	cleanup_heredoc_tracking(sh);
	init_heredoc_tracking(sh);
}

void	cleanup_shell_resources(t_shell *sh)
{
	if (sh->all_tokens)
	{
		free_tokens(sh->all_tokens);
		sh->all_tokens = NULL;
	}
	if (sh->all_cmds)
	{
		free_cmds(sh->all_cmds);
		sh->all_cmds = NULL;
	}
	if (sh->env)
	{
		ft_free_split(sh->env);
		sh->env = NULL;
	}
	if (sh->heredoc_fds)
		cleanup_heredoc_tracking(sh);
}

void	cleanup_after_execution(t_shell *sh)
{
	if (sh->all_tokens)
	{
		free_tokens(sh->all_tokens);
		sh->all_tokens = NULL;
	}
	if (sh->all_cmds)
	{
		free_cmds(sh->all_cmds);
		sh->all_cmds = NULL;
	}
	close_all_heredoc_fds(sh);
	cleanup_heredoc_tracking(sh);
	init_heredoc_tracking(sh);
}
