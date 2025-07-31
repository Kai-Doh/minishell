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

static void	handle_char_expansion(t_expansion_ctx *ctx, t_shell *sh)
{
	if (ctx->input[*ctx->index] == '\\' && ctx->qs->in_double)
		handle_escape_chars(ctx->result, ctx->input, ctx->index,
			ctx->qs->in_double);
	else if (ctx->input[*ctx->index] == '$'
		&& (ctx->input[*ctx->index + 1] == '"'
			|| ctx->input[*ctx->index + 1] == '\'')
		&& ctx->qs->in_single == 0 && ctx->qs->in_double == 0)
	{
		(*ctx->index)++;
		process_quote_state(ctx->input[*ctx->index], &ctx->qs->in_single,
			&ctx->qs->in_double);
		(*ctx->index)++;
	}
	else if ((ctx->input[*ctx->index] == '\'' && ctx->qs->in_double == 0)
		|| (ctx->input[*ctx->index] == '"' && ctx->qs->in_single == 0))
	{
		process_quote_state(ctx->input[*ctx->index], &ctx->qs->in_single,
			&ctx->qs->in_double);
		(*ctx->index)++;
	}
	else if (ctx->input[*ctx->index] == '$' && ctx->qs->in_single == 0)
		process_expansion_logic(ctx->result, ctx->input, ctx->index, sh);
	else
		*ctx->result = append_char(*ctx->result, ctx->input[(*ctx->index)++]);
}

static void	process_expansion(char **res, char *s, t_shell *sh)
{
	size_t			i;
	t_quote_state	qs;
	t_expansion_ctx	ctx;

	i = 0;
	qs.in_single = 0;
	qs.in_double = 0;
	ctx.result = res;
	ctx.input = s;
	ctx.index = &i;
	ctx.qs = &qs;
	while (s && s[i])
		handle_char_expansion(&ctx, sh);
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
