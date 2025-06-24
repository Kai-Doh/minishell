/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:42:20 by ktiomico          #+#    #+#             */
/*   Updated: 2025/05/26 11:56:15 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**g_env;
int g_last_exit_status;

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	if (argc != 1)
		exit_msg(ARGS, ERROR);
    g_env = dup_env(env);
    g_last_exit_status = 0;
	setup_signals();
	start_shell_loop(g_env);
	return (0);
}
