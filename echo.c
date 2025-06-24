#include "minishell.h"

static char *strip_quotes(char *str)
{
    size_t len;

    if (!str)
        return (NULL);
    len = ft_strlen(str);
    if (len >= 2 && ((str[0] == '\'' && str[len - 1] == '\'') ||
        (str[0] == '"' && str[len - 1] == '"')))
        return (ft_substr(str, 1, len - 2));
    return (ft_strdup(str));
}

void    builtin_echo(char *arg)
{
    char *output;

    if (!arg)
    {
        printf("\n");
        return ;
    }
    output = strip_quotes(arg);
    if (output)
    {
        printf("%s\n", output);
        free(output);
    }
    else
        printf("%s\n", arg);
}

