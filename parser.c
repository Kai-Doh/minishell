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

char	*expand_word(char *s, t_shell *sh)
{
	char	*res;
	size_t	i;
	int		in_s;
	int		in_d;

	res = NULL;
	i = 0;
	in_s = 0;
	in_d = 0;
	res = ft_strdup("");
	while (s && s[i])
	{
		if (s[i] == '\'' && in_d == 0)
			in_s = 1 - in_s;
		else if (s[i] == '"' && in_s == 0)
			in_d = 1 - in_d;
		else if (s[i] == '$' && in_s == 0)
			handle_dollar_expand(&res, s, &i, sh);
		else
			res = append_char(res, s[i++]);
		if (s[i - 1] == '\'' || s[i - 1] == '"')
			i++;
	}
	return (res);
}
