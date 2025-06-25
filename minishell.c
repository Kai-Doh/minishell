/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: thofstet <thofstet@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 00:32:22 by thofstet          #+#    #+#             */
/*   Updated: 2025/04/13 00:32:29 by thofstet         ###   ########.fr       */
=======
/*   By: github <github@kaidoh.ch>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 22:24:51 by github            #+#    #+#             */
/*   Updated: 2025/06/24 22:24:51 by github           ###   ########.fr       */
>>>>>>> karl
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD
int     handle_input(char *rl)
{
        if (ft_strncmp(rl, "exit", 4) == 0)
                return (1);
        if (ft_strncmp(rl, "echo ", 5) == 0)
        {
                builtin_echo(rl + 5);
                return (0);
        }
        if (ft_strncmp(rl, "echo", 4) == 0 && rl[4] == '\0')
        {
                builtin_echo(NULL);
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
		if (handle_input(rl))
		{
			free(rl);
			break ;
		}
		free(rl);
	}
}

=======
>>>>>>> karl
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
