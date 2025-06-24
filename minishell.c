#include "minishell.h"

int main(int argc, char **argv, char **env)
{
    t_shell sh;

    (void)argv;
    if (argc != 1)
        exit_msg(ARGS, ERROR, NULL);
    sh.env = dup_env(env);
    sh.last_exit_status = 0;
    setup_signals();
    start_shell_loop(&sh);
    ft_free_split(sh.env);
    return (0);
}
