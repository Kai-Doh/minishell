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

t_token	*lexer_loop(char *s, int *i, int *error)
{
	t_token	*head;
	t_token	*cur;
	t_token	*new;
	char	*val;

	head = NULL;
	val = extract_token(s, i, error);
	while (val != NULL)
	{
		new = malloc(sizeof(t_token));
		if (new == NULL)
			return (free_tokens(head), NULL);
		new->content = val;
		new->type = get_type(val);
		new->next = NULL;
		if (head == NULL)
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
