/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thofstet <thofstet@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:08:22 by thofstet          #+#    #+#             */
/*   Updated: 2025/04/14 18:31:39 by thofstet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    execute_ls(char **env)
{
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork error");
        return;
    }
    else if (pid == 0) // Processus fils
    {
        char *args[] = {"ls", NULL};
        if (execve("/bin/ls", args, env) == -1)
        {
            perror("execve error frérot");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        wait(NULL); // On attend la fin du processus fils
    }
}

/*
Fork/execve : La fonction "execute_ls" crée un processus fils qui
exécute /bin/ls en utilisant execve(). Le parent attends la fin
du fils.

Dans handle_input, si l'entrée est "ls" -> on lance execute_ls.

Et on transmet l'env du main jusqu'à execve.

Explications un peu inutile mais wola quand on aura une tonne de
commandes on sera contents de pouvoir tout recheck mdr.
*/