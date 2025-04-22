/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thofstet <thofstet@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:42:20 by ktiomico          #+#    #+#             */
/*   Updated: 2025/04/22 06:12:02 by thofstet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_input(char *rl, char **env)
{
	t_token	*tok;

	tok = lexer(rl);
	if (!tok)
		return (0);
	if (tok_is_builtin_exit(tok))
	{
		ft_tokclear(&tok);
		return (1);
	}
	exec_pipeline(tok, env);
	ft_tokclear(&tok);
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

	(void)argv;
	if (argc != 1)
		exit_msg(ARGS, ERROR);
	start_shell_loop(env);
	return (0);
}
