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

static int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static t_type	get_type(char *s)
{
	if (s[0] == '|' && !s[1])
		return (PIPE);
	if (s[0] == '<' && s[1] == '<')
		return (HEREDOC);
	if (s[0] == '>' && s[1] == '>')
		return (APPEND);
	if (s[0] == '<')
		return (REDIR_IN);
	if (s[0] == '>')
		return (REDIR_OUT);
	return (WORD);
}


static char     *extract_token(char *s, int *i)
{
        int             start;
        char    quote;
        char    *raw;

        while (is_space(s[*i]))
                (*i)++;
        start = *i;
        if (!s[start])
                return (NULL);
        if (s[*i] == '<' || s[*i] == '>' || s[*i] == '|')
        {
                (*i)++;
                if (s[*i] == s[start])
                        (*i)++;
        }
        else
        {
                while (s[*i] && !is_space(s[*i])
                        && s[*i] != '<' && s[*i] != '>' && s[*i] != '|')
                {
                        if (s[*i] == '\'' || s[*i] == '"')
                        {
                                quote = s[*i];
                                (*i)++;
                                while (s[*i] && s[*i] != quote)
                                        (*i)++;
                                if (s[*i] == quote)
                                        (*i)++;
                        }
                        else
                                (*i)++;
                }
        }
        raw = ft_substr(s, start, *i - start);
        if (!raw)
                return (NULL);
        s = remove_quotes(raw);
        free(raw);
        return (s);
}
t_token	*lexer(char *s)
{
	t_token	*head;
	t_token	*cur;
	t_token	*new;
	char	*val;
	int		i;

	i = 0;
	head = NULL;
	while ((val = extract_token(s, &i)))
	{
		new = malloc(sizeof(t_token));
		new->content = val;
		new->type = get_type(val);
		new->next = NULL;
		if (!head)
			head = new;
		else
			cur->next = new;
		cur = new;
	}
	return (head);
}
