/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github <github@kaidoh.ch>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 23:19:15 by github            #+#    #+#             */
/*   Updated: 2025/06/24 23:19:16 by github           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	scan_token(char *s, int *i, int *in_s, int *in_d)
{
	while (s[*i] != '\0' && (!is_space(s[*i]) || *in_s || *in_d))
	{
		if (s[*i] == '\'' && *in_d == 0)
			*in_s = 1 - *in_s;
		else if (s[*i] == '"' && *in_s == 0)
			*in_d = 1 - *in_d;
		else if (*in_s == 0 && *in_d == 0 && is_special(s[*i]))
			break ;
		(*i)++;
	}
	return (*in_s || *in_d);
}

char	*extract_token(char *s, int *i)
{
	int	start;
	int	in_s;
	int	in_d;

	while (is_space(s[*i]))
		(*i)++;
	start = *i;
	if (s[start] == '\0')
		return (NULL);
	if (is_special(s[*i]))
	{
		(*i)++;
		if (s[*i] == s[start])
			(*i)++;
	}
	else
	{
		in_s = 0;
		in_d = 0;
		if (scan_token(s, i, &in_s, &in_d))
			return (quote_error(in_s), NULL);
	}
	return (ft_substr(s, start, *i - start));
}

t_type	get_type(char *s)
{
	if (s[0] == '|' && s[1] == '\0')
		return (PIPE);
	if (s[0] == '<' && s[1] == '<')
		return (HEREDOC);
	if (s[0] == '>' && s[1] == '>')
		return (APPEND);
	if (s[0] == '<')
		return (REDIR_IN);
	if (s[0] == '>')
		return (REDIR_OUT);
	return (WORD);
}
