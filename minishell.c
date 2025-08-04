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
	setup_signals();
	start_shell_loop(&sh);
	ft_free_split(sh.env);
	return (0);
}
