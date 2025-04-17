/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexertemp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:00:30 by ktiomico          #+#    #+#             */
/*   Updated: 2025/04/17 14:00:04 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*lex_word(char *line, size_t *i);

void    add_token(t_token **lst, char *content, t_type type)
{
    t_token *new;

    if (!content)
        return ;
    new = malloc(sizeof(*new));
    if (!new)
        return ;
    new->content = content;
    new->type = type;
    new->next = NULL;
    if (*lst == NULL)
        *lst = new;
    else
    {
        t_token *tmp = *lst;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
}


t_token	*lexer(char *line)
{
	size_t	i;
	char	*word;
	t_token	*lst;

	i = 0;
	lst = NULL;
	while (line && line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else if (line[i] == '|')
		{
			tok_add_back(&lst, tok_new(ft_strdup("|"), PIPE));
			i++;
		}
		else
		{
			word = lex_word(line, &i);
			tok_add_back(&lst, tok_new(word, WORD));
		}
	}
	return (lst);
}

void    free_token_list(t_token **lst)
{
    t_token *tmp;

    while (lst && *lst)
    {
        tmp = (*lst)->next;
        free((*lst)->content);
        free(*lst);
        *lst = tmp;
    }
}

static char	*quoted(char *line, size_t *i, char quote)
{
	size_t	start;
	size_t	len;

	start = ++(*i);
	while (line[*i] && line[*i] != quote)
		(*i)++;
	len = *i - start;
	if (line[*i] == quote)
		(*i)++;
	return (ft_substr(line, start, len));
}

char	*lex_word(char *line, size_t *i)
{
	size_t	start;

	if (line[*i] == '\"')
		return (quoted(line, i, '\"'));
	if (line[*i] == '\'')
		return (quoted(line, i, '\''));
	start = *i;
	while (line[*i] && !ft_isspace(line[*i]) && line[*i] != '|')
		(*i)++;
	return (ft_substr(line, start, *i - start));
}
