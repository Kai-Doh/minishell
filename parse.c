#include "minishell.h"

static int count_parts(char **parts)
{
    int i = 0;
    if (!parts)
        return (0);
    while (parts[i])
        i++;
    return (i);
}

static char *ft_strdup_safe(char *s)
{
    if (!s)
        return (NULL);
    return (ft_strdup(s));
}

static void free_split(char **tab)
{
    int i = 0;
    if (!tab)
        return ;
    while (tab[i])
        free(tab[i++]);
    free(tab);
}

static void fill_cmd(t_cmd *cmd, char **tokens)
{
    int i = 0;
    int argc = 0;

    cmd->infile = NULL;
    cmd->outfile = NULL;
    while (tokens[i])
    {
        if (strcmp(tokens[i], "<") == 0 && tokens[i + 1])
        {
            cmd->infile = ft_strdup_safe(tokens[i + 1]);
            i += 2;
        }
        else if (strcmp(tokens[i], ">") == 0 && tokens[i + 1])
        {
            cmd->outfile = ft_strdup_safe(tokens[i + 1]);
            i += 2;
        }
        else
        {
            argc++;
            i++;
        }
    }
    cmd->args = malloc(sizeof(char *) * (argc + 1));
    i = 0;
    argc = 0;
    while (tokens[i])
    {
        if (strcmp(tokens[i], "<") == 0 || strcmp(tokens[i], ">") == 0)
        {
            i += 2;
            continue ;
        }
        cmd->args[argc++] = ft_strdup_safe(tokens[i]);
        i++;
    }
    cmd->args[argc] = NULL;
}

int parse_input(char *line, t_cmd **cmds_out)
{
    char    **parts;
    int     count;
    int     i;

    parts = ft_split(line, '|');
    count = count_parts(parts);
    if (count == 0)
    {
        *cmds_out = NULL;
        free_split(parts);
        return (0);
    }
    *cmds_out = malloc(sizeof(t_cmd) * count);
    if (!*cmds_out)
        return (free_split(parts), 0);
    i = 0;
    while (i < count)
    {
        char **tokens = ft_split(parts[i], ' ');
        if (!tokens)
            return (free_split(parts), free(*cmds_out), *cmds_out = NULL, 0);
        fill_cmd(&(*cmds_out)[i], tokens);
        free_split(tokens);
        i++;
    }
    free_split(parts);
    return (count);
}

void free_cmds(t_cmd *cmds, int count)
{
    int i, j;

    if (!cmds)
        return ;
    i = 0;
    while (i < count)
    {
        j = 0;
        while (cmds[i].args && cmds[i].args[j])
            free(cmds[i].args[j++]);
        free(cmds[i].args);
        free(cmds[i].infile);
        free(cmds[i].outfile);
        i++;
    }
    free(cmds);
}

bool is_builtin(char *cmd)
{
    if (!cmd)
        return (false);
    return (strcmp(cmd, "echo") == 0);
}
