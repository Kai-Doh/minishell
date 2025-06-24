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

int	g_lexer_error = 0;

t_token	*lexer_loop(char *s, int *i)
{
	t_token	*head;
	t_token	*cur;
	t_token	*new;
	char	*val;

	head = NULL;
	val = extract_token(s, i);
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
		val = extract_token(s, i);
	}
	return (head);
}

t_token	*lexer(char *s)
{
	t_token	*head;
	int		i;

	i = 0;
	head = lexer_loop(s, &i);
	if (g_lexer_error != 0)
	{
		free_tokens(head);
		return (NULL);
	}
	return (head);
}
