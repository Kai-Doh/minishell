#include "minishell.h"

/*
 * Print the given argument line like the real bash echo without options.
 * Quotes are removed and spaces preserved. This is a very small parser that
 * understands single and double quotes and treats everything else literally.
 */
void    builtin_echo(char *arg_line)
{
    bool    in_single;
    bool    in_double;

    if (!arg_line)
    {
        printf("\n");
        return ;
    }
    in_single = false;
    in_double = false;
    while (*arg_line)
    {
        if (*arg_line == '\'' && !in_double)
        {
            in_single = !in_single;
            arg_line++;
            continue ;
        }
        if (*arg_line == '"' && !in_single)
        {
            in_double = !in_double;
            arg_line++;
            continue ;
        }
        if (*arg_line == ' ' && !in_single && !in_double)
        {
            putchar(' ');
            while (*arg_line == ' ')
                arg_line++;
            continue ;
        }
        putchar(*arg_line);
        arg_line++;
    }
    putchar('\n');
}

