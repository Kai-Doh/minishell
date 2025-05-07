/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thofstet <thofstet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:55:13 by thofstet          #+#    #+#             */
/*   Updated: 2025/05/07 17:55:37 by thofstet         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	**envp;

	(void)argv;
	if (argc != 1)
		exit_msg(ARGS, ERROR);
	envp = copy_env(env);
	if (!envp)
	{
		ft_putendl_fd("minishell: failed to copy environment", 2);
		return (1);
	}
	setup_signals();
	start_shell_loop(envp);
	free_env(envp);
	return (0);
}
