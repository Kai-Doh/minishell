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

char	*append_str(char *base, const char *add)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strjoin(base, add);
	free(base);
	return (tmp);
}

char	*append_char(char *base, char c)
{
	char	str[2];

	str[0] = c;
	str[1] = '\0';
	return (append_str(base, str));
}

char	*get_env_value(char *name, t_shell *sh)
{
	int		i;
	size_t	len;

	i = 0;
	len = 0;
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
	return ("");
}

int	handle_word_token(t_cmd *cmd, t_token **tok, t_shell *sh)
{
	char	*arg;

	arg = expand_word((*tok)->content, sh);
	if (!cmd->args && is_variable_assignment(arg))
	{
		if (handle_variable_assignment(arg, sh))
		{
			free(arg);
			return (1);
		}
		free(arg);
	}
	else if (arg && arg[0] != '\0')
	{
		cmd->args = ft_args_add(cmd->args, arg);
		if (!cmd->args)
			return (1);
	}
	else
		free(arg);
	*tok = (*tok)->next;
	return (0);
}
