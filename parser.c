/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:58:00 by ktiomico          #+#    #+#             */
/*   Updated: 2025/04/29 14:16:30 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_dollar_expand(char **res, char *s, size_t *i, t_shell *sh)
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

static void	process_quote_state(char c, int *in_s, int *in_d)
{
	if (c == '\'' && *in_d == 0)
		*in_s = 1 - *in_s;
	else if (c == '"' && *in_s == 0)
		*in_d = 1 - *in_d;
}

static void	process_expansion_logic(char **res, char *s, size_t *i, t_shell *sh)
{
	if (s[*i] == '$')
	{
		if (s[*i + 1] == '?' || ft_isalpha(s[*i + 1]) || s[*i + 1] == '_')
			handle_dollar_expand(res, s, i, sh);
		else
		{
			*res = append_char(*res, '$');
			(*i)++;
		}
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
		if ((s[i] == '\'' && in_d == 0) || (s[i] == '"' && in_s == 0))
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

	res = ft_strdup("");
	process_expansion(&res, s, sh);
	return (res);
}
