/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thofstet <thofstet@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:42:20 by ktiomico          #+#    #+#             */
/*   Updated: 2025/04/14 18:24:58 by thofstet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_input(char *rl, char **env)
{
	if (ft_strncmp(rl, "exit", 4) == 0)
		return (1);
	if (ft_strncmp(rl, "ls", 2) == 0)
	{
		execute_ls(env);
		return (0);
	}
	printf(PURPLE "42\n" RESET);
	return (0);
}

void	start_shell_loop(char **env)
{
	char	*rl;
	char	*prompt_str;

	(void)env;
	while (1)
	{
		prompt_str = prompt();
		if (!prompt_str)
			continue ;
		rl = readline(prompt_str);
		free(prompt_str);
		if (!rl)
			break ;
		if (handle_input(rl, env))
		{
			free(rl);
			break ;
		}
		free(rl);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argv;
	(void)data;
	if (argc != 1)
		exit_msg(ARGS, ERROR);
	start_shell_loop(env);
	return (0);
}
