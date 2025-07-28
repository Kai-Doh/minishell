/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:00:00 by ktiomico          #+#    #+#             */
/*   Updated: 2025/07/28 16:00:00 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_quote_state(char c, int *in_s, int *in_d)
{
	if (c == '\'' && *in_d == 0)
		*in_s = 1 - *in_s;
	else if (c == '"' && *in_s == 0)
		*in_d = 1 - *in_d;
}

void	process_expansion_logic(char **res, char *s, size_t *i, t_shell *sh)
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
