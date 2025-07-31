/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 22:24:51 by ktiomico          #+#    #+#             */
/*   Updated: 2025/06/24 22:24:51 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	sh;

	(void)argv;
	if (argc != 1)
		exit_msg(ARGS, ERROR, NULL);
	sh.env = dup_env(env);
	if (!sh.env)
		exit_msg("Memory allocation failed", 1, NULL);
	increment_shlvl(&sh);
	sh.last_exit_status = 0;
	sh.should_exit = 0;
	sh.all_tokens = NULL;
	sh.all_cmds = NULL;
	init_heredoc_tracking(&sh);
	setup_signals();
	start_shell_loop(&sh);
	cleanup_heredoc_tracking(&sh);
	cleanup_all_fds();
	ft_free_split(sh.env);
	clear_history();
	return (sh.last_exit_status);
}
