/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:00:00 by ktiomico          #+#    #+#             */
/*   Updated: 2025/07/28 16:00:00 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_dollar_expand(char **res, char *s, size_t *i, t_shell *sh)
{
	char	*tmp;
	char	*name;
	size_t	start;

	tmp = NULL;
	name = NULL;
	start = 0;
	if (s[*i + 1] == '?')
	{
		tmp = ft_itoa(sh->last_exit_status);
		*res = append_str(*res, tmp);
		free(tmp);
		*i += 2;
	}
	else if (ft_isalpha(s[*i + 1]) || s[*i + 1] == '_')
	{
		(*i)++;
		start = *i;
		while (ft_isalnum(s[*i]) || s[*i] == '_')
			(*i)++;
		name = ft_substr(s, start, *i - start);
		*res = append_str(*res, get_env_value(name, sh));
		free(name);
	}
}

static void	handle_escape_chars(char **res, char *s, size_t *i, int in_d)
{
	if (s[*i] == '\\' && in_d && s[*i + 1] == '"')
	{
		*res = append_char(*res, '"');
		*i += 2;
	}
	else if (s[*i] == '\\' && in_d && s[*i + 1] == '\\')
	{
		*res = append_char(*res, '\\');
		*i += 2;
	}
	else
	{
		*res = append_char(*res, s[*i]);
		(*i)++;
	}
}

static void	process_expansion(char **res, char *s, t_shell *sh)
{
	size_t	i;
	int		in_s;
	int		in_d;

	i = 0;
	in_s = 0;
	in_d = 0;
	while (s && s[i])
	{
		if (s[i] == '\\' && in_d)
			handle_escape_chars(res, s, &i, in_d);
		else if ((s[i] == '\'' && in_d == 0) || (s[i] == '"' && in_s == 0))
		{
			process_quote_state(s[i], &in_s, &in_d);
			i++;
		}
		else if (s[i] == '$' && in_s == 0)
			process_expansion_logic(res, s, &i, sh);
		else
		{
			*res = append_char(*res, s[i]);
			i++;
		}
	}
}

char	*expand_word(char *s, t_shell *sh)
{
	char	*res;
	char	*wildcard_res;

	res = ft_strdup("");
	process_expansion(&res, s, sh);
	wildcard_res = expand_wildcards(res);
	free(res);
	return (wildcard_res);
}
