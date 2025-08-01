/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github <github@kaidoh.ch>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 23:39:02 by github            #+#    #+#             */
/*   Updated: 2025/06/24 23:39:04 by github           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_pwd_env(char *name, t_shell *sh)
{
	(void)sh;
	if (name && ((!ft_strncmp(name, "PWD", 3) && name[3] == '\0')
			|| (!ft_strncmp(name, "HOME", 4) && name[4] == '\0')))
		return ("");
	return ("");
}

char	*get_env_value(char *name, t_shell *sh)
{
	int		i;
	size_t	len;

	i = 0;
	if (!name)
		return ("");
	len = ft_strlen(name);
	while (sh->env && sh->env[i])
	{
		if (!ft_strncmp(sh->env[i], name, len)
			&& sh->env[i][len] == '=')
			return (sh->env[i] + len + 1);
		i++;
	}
	return (handle_pwd_env(name, sh));
}

static int	has_quotes(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

int	handle_word_token(t_cmd *cmd, t_token **tok, t_shell *sh)
{
	char	*arg;
	int		had_quotes;

	arg = expand_word((*tok)->content, sh);
	had_quotes = has_quotes((*tok)->content);
	if (!cmd->args && is_variable_assignment(arg))
	{
		if (handle_variable_assignment(arg, sh))
		{
			free(arg);
			return (1);
		}
		free(arg);
	}
	else if (arg && (arg[0] != '\0' || had_quotes))
	{
		cmd->args = ft_strs_add(cmd->args, arg);
		free(arg);
		if (!cmd->args)
			return (1);
	}
	else
		free(arg);
	*tok = (*tok)->next;
	return (0);
}

int	is_all_operators(t_token *tok)
{
	while (tok)
	{
		if (tok->type == WORD)
			return (0);
		tok = tok->next;
	}
	return (1);
}
