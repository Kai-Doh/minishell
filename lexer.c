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


int g_lexer_error = 0;

static char     *extract_token(char *s, int *i)
{
        int             start;
        int             in_s;
        int             in_d;

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
               in_s = 0;
               in_d = 0;
               while (s[*i] && (!is_space(s[*i]) || in_s || in_d))
               {
                       if (s[*i] == '\'' && !in_d)
                               in_s = !in_s;
                       else if (s[*i] == '"' && !in_s)
                               in_d = !in_d;
                       else if (!in_s && !in_d
                                && (s[*i] == '<' || s[*i] == '>' || s[*i] == '|'))
                               break ;
                       (*i)++;
               }
               if (in_s || in_d)
               {
                       ft_putstr_fd("minishell: unexpected EOF while looking for matching '", 2);
                       ft_putchar_fd(in_s ? '\'' : '"', 2);
                       ft_putendl_fd("'", 2);
                       g_lexer_error = 1;
                       return (NULL);
               }
       }
       return (ft_substr(s, start, *i - start));
}
t_token	*lexer(char *s)
{
	t_token	*head;
	t_token	*cur;
	t_token	*new;
	char	*val;
	int		i;

       i = 0;
       g_lexer_error = 0;
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
       if (g_lexer_error)
       {
               free_tokens(head);
               return (NULL);
       }
       return (head);
}
