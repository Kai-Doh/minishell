/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github <github@kaidoh.ch>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 23:45:00 by github            #+#    #+#             */
/*   Updated: 2025/06/24 23:45:02 by github           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_initial_tokens(t_token *tok, t_shell *sh)
{
	if (!tok)
		return (0);
	if (tok->type == PIPE)
	{
		sh->last_exit_status = 2;
		return (1);
	}
	if (is_all_operators(tok))
	{
		sh->last_exit_status = 2;
		return (1);
	}
	return (0);
}

static int	check_pipe_error(t_token *curr, t_shell *sh)
{
	if (curr->type == PIPE)
	{
		if (!curr->next)
		{
			sh->last_exit_status = 2;
			return (1);
		}
		if (curr->next->type == PIPE)
		{
			sh->last_exit_status = 2;
			return (1);
		}
	}
	return (0);
}

static int	check_redir_error(t_token *curr, t_shell *sh)
{
	if (curr->type >= REDIR_IN && curr->type <= APPEND
		&& (!curr->next || curr->next->type != WORD))
	{
		sh->last_exit_status = 2;
		return (1);
	}
	return (0);
}

static int	validate_token_sequence(t_token *tok, t_shell *sh)
{
	t_token	*curr;
	t_token	*prev;

	curr = tok;
	prev = NULL;
	while (curr)
	{
		if (check_pipe_error(curr, sh) || check_redir_error(curr, sh))
			return (1);
		prev = curr;
		curr = curr->next;
	}
	if (prev && prev->type == PIPE)
	{
		sh->last_exit_status = 2;
		return (1);
	}
	return (0);
}

int	validate_syntax(t_token *tok, t_shell *sh)
{
	if (validate_initial_tokens(tok, sh))
		return (1);
	return (validate_token_sequence(tok, sh));
}
