/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 00:00:00 by ktiomico          #+#    #+#             */
/*   Updated: 2025/05/31 00:00:00 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char     *get_env_value(char *name, t_shell *sh)
{
    int     i;
    size_t  len;

    if (!name)
        return "";
    len = ft_strlen(name);
    i = 0;
    while (sh->env && sh->env[i])
    {
        if (!ft_strncmp(sh->env[i], name, len) && sh->env[i][len] == '=')
            return (sh->env[i] + len + 1);
        i++;
    }
    return "";
}

static char     *append_str(char *base, const char *add)
{
    char    *tmp;

    tmp = ft_strjoin(base, add);
    free(base);
    return (tmp);
}

static void     toggle_quotes(char c, int *in_s, int *in_d)
{
    if (c == '\'' && !*in_d)
        *in_s = !*in_s;
    else if (c == '"' && !*in_s)
        *in_d = !*in_d;
}

static char     *expand_var(char *res, char *s, size_t *i, t_shell *sh)
{
    char    *tmp; size_t  start;
    if (s[*i + 1] == '?')
    {
        tmp = ft_itoa(sh->last_exit_status);
        res = append_str(res, tmp);
        free(tmp);
        *i += 2;
        return (res);
    }
    if (ft_isalpha(s[*i + 1]) || s[*i + 1] == '_')
    {
        start = ++(*i);
        while (ft_isalnum(s[*i]) || s[*i] == '_')
            (*i)++;
        tmp = ft_substr(s, start, *i - start);
        res = append_str(res, get_env_value(tmp, sh));
        free(tmp);
        return (res);
    }
    res = append_str(res, "$");
    (*i)++;
    return (res);
}

char    *expand_word(char *s, t_shell *sh)
{
    char    *res;
    size_t  i;
    int             in_s;
    int             in_d;
    char    str[2];

    res = ft_strdup("");
    i = 0;
    in_s = 0;
    in_d = 0;
    while (s && s[i])
    {
        if (s[i] == '\'' || s[i] == '"')
        {
            toggle_quotes(s[i], &in_s, &in_d);
            i++;
        }
        else if (s[i] == '$' && !in_s)
            res = expand_var(res, s, &i, sh);
        else
        {
            str[0] = s[i++];
            str[1] = '\0';
            res = append_str(res, str);
        }
    }
    return (res);
}
