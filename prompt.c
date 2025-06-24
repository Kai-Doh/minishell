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
static int	handle_input(char *rl, t_shell *sh);

void	start_shell_loop(t_shell *sh)
{
	char	*rl;
	char	*prompt_str;

	while (1)
    {
		g_signal = 0;
		prompt_str = prompt();
		if (!prompt_str)
			continue ;
		rl = readline(prompt_str);
		free(prompt_str);
		if (g_signal == SIGINT)
        {
			sh->last_exit_status = 130;
            g_signal = 0;
            free(rl);
            continue ;
        }
        if (!rl)
            break ;
        if (handle_input(rl, sh))
        {
            free(rl);
            break ;
        }
        free(rl);
	}
}

static int	handle_input(char *rl, t_shell *sh)
{
	t_token	*tokens;
	t_cmd	*cmds;

	if (!rl || rl[0] == '\0')
		return (0);
	add_history(rl);
    tokens = NULL;
    int err = 0;
    tokens = lexer(rl, &err);
    if (!tokens)
    {
		if (err)
			sh->last_exit_status = 2;
		return (0);
	}
	cmds = parse(tokens, sh);
	if (!cmds)
		return (0);
	execute(cmds, sh);
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
