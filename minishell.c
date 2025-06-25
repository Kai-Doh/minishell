/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github <github@kaidoh.ch>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 22:24:51 by github            #+#    #+#             */
/*   Updated: 2025/06/24 22:24:51 by github           ###   ########.fr       */
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
	sh.last_exit_status = 0;
	setup_signals();
	start_shell_loop(&sh);
	ft_free_split(sh.env);
	return (0);
}
