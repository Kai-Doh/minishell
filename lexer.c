/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:00:30 by ktiomico          #+#    #+#             */
/*   Updated: 2025/04/29 14:15:57 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*create_token(char *val, t_token *head)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
	{
		free(val);
		free_tokens(head);
		return (NULL);
	}
	new->content = val;
	new->type = get_type(val);
	new->next = NULL;
	return (new);
}

t_token	*lexer_loop(char *s, int *i, int *error)
{
	t_token	*head;
	t_token	*cur;
	t_token	*new;
	char	*val;

	head = NULL;
	val = extract_token(s, i, error);
	while (val)
	{
		new = create_token(val, head);
		if (!new)
		{
			free_tokens(head);
			return (NULL);
		}
		if (!head)
			head = new;
		else
			cur->next = new;
		cur = new;
		val = extract_token(s, i, error);
	}
	return (head);
}

t_token	*lexer(char *s, int *error)
{
	t_token	*head;
	int		i;

	i = 0;
	if (error)
		*error = 0;
	head = lexer_loop(s, &i, error);
	if (error && *error != 0)
	{
		free_tokens(head);
		return (NULL);
	}
	return (head);
}
