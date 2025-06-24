#include "minishell.h"

static void free_split(char **tab)
{
    int i = 0;
    if (!tab)
        return ;
    while (tab[i])
        free(tab[i++]);
    free(tab);
}

static char *find_command_path(char *cmd, char **env)
{
    char    *path_env;
    char    **paths;
    char    *joined;
    int     i;

    if (!cmd || ft_strchr(cmd, '/'))
        return (ft_strdup(cmd));
    path_env = getenv("PATH");
    if (!path_env)
    {
        i = 0;
        while (env && env[i])
        {
            if (ft_strncmp(env[i], "PATH=", 5) == 0)
            {
                path_env = env[i] + 5;
                break ;
            }
            i++;
        }
    }
    if (!path_env)
        return (NULL);
    paths = ft_split(path_env, ':');
    i = 0;
    while (paths && paths[i])
    {
        char *tmp = ft_strjoin(paths[i], "/");
        joined = ft_strjoin(tmp, cmd);
        free(tmp);
        if (access(joined, X_OK) == 0)
            return (free_split(paths), joined);
        free(joined);
        i++;
    }
    free_split(paths);
    return (NULL);
}

static int open_redirs(t_cmd *cmd)
{
    int fd;

    if (cmd->infile)
    {
        fd = open(cmd->infile, O_RDONLY);
        if (fd < 0 || dup2(fd, STDIN_FILENO) < 0)
            return (perror(cmd->infile), -1);
        close(fd);
    }
    if (cmd->outfile)
    {
        fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0)
            return (perror(cmd->outfile), -1);
        close(fd);
    }
    return (0);
}

static void run_builtin(t_cmd *cmd)
{
    if (strcmp(cmd->args[0], "echo") == 0)
        builtin_echo(cmd->args[1]);
}

int execute_commands(t_cmd *cmds, int count, char **env)
{
    int     i;
    int     prev_fd = -1;
    int     pipefd[2];
    pid_t   *pids = malloc(sizeof(pid_t) * count);

    if (!pids)
        return (perror("malloc"), -1);
    i = 0;
    while (i < count)
    {
        if (i < count - 1 && pipe(pipefd) < 0)
            return (perror("pipe"), free(pids), -1);
        if (is_builtin(cmds[i].args[0]) && count == 1)
        {
            int save_in = dup(STDIN_FILENO);
            int save_out = dup(STDOUT_FILENO);
            if (open_redirs(&cmds[i]) < 0)
                return (free(pids), -1);
            run_builtin(&cmds[i]);
            dup2(save_in, STDIN_FILENO);
            dup2(save_out, STDOUT_FILENO);
            close(save_in);
            close(save_out);
            free(pids);
            return (0);
        }
        pids[i] = fork();
        if (pids[i] == 0)
        {
            if (prev_fd != -1)
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            if (i < count - 1)
            {
                close(pipefd[0]);
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);
            }
            if (open_redirs(&cmds[i]) < 0)
                exit(1);
            if (is_builtin(cmds[i].args[0]))
            {
                run_builtin(&cmds[i]);
                exit(0);
            }
            char *path = find_command_path(cmds[i].args[0], env);
            if (!path)
                exit(1);
            execve(path, cmds[i].args, env);
            perror(cmds[i].args[0]);
            exit(1);
        }
        if (prev_fd != -1)
            close(prev_fd);
        if (i < count - 1)
        {
            close(pipefd[1]);
            prev_fd = pipefd[0];
        }
        i++;
    }
    if (prev_fd != -1)
        close(prev_fd);
    i = 0;
    while (i < count)
        waitpid(pids[i++], NULL, 0);
    free(pids);
    return (0);
}
