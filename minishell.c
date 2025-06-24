/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thofstet <thofstet@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 00:32:22 by thofstet          #+#    #+#             */
/*   Updated: 2025/04/13 00:32:29 by thofstet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     handle_input(char *rl, char **env)
{
        t_cmd   *cmds;
        int             count;

        if (ft_strncmp(rl, "exit", 4) == 0 && (rl[4] == '\0' || isspace((unsigned char)rl[4])))
                return (1);
        count = parse_input(rl, &cmds);
        if (count <= 0)
                return (0);
        execute_commands(cmds, count, env);
        free_cmds(cmds, count);
        return (0);
}

void	start_shell_loop(char **env)
{
	char	*rl;
	char	*prompt_str;

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
