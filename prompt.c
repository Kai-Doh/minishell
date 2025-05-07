/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:10:08 by ktiomico          #+#    #+#             */
/*   Updated: 2025/04/29 14:25:01 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*prompt(void);
static int	handle_input(char *rl, char **env);

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

static int	handle_input(char *rl, char **env)
{
	t_token	*tokens;
	t_cmd	*cmds;

	if (!rl || rl[0] == '\0')
		return (0);
	add_history(rl);
	tokens = lexer(rl);
	if (!tokens)
		return (0);
	cmds = parse(tokens);
	if (!cmds)
		return (0);
	execute(cmds, env);
	free_tokens(tokens);
	free_cmds(cmds);
	return (0);
}

static char	*prompt(void)
{
	char	*username;
	char	*start;
	char	*end;
	char	*full;
	int		len;

	username = getenv("USER");
	if (!username)
		username = "unknown";
	start = GREEN "👾 Minishell" YELLOW "@";
	end = GREEN " ➜ " RESET;
	len = ft_strlen(start) + ft_strlen(username) + ft_strlen(end) + 1;
	full = malloc(len);
	if (!full)
		return (NULL);
	ft_strlcpy(full, start, len);
	ft_strlcat(full, username, len);
	ft_strlcat(full, end, len);
	return (full);
}
