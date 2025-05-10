/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thofstet <thofstet>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:19:31 by thofstet          #+#    #+#             */
/*   Updated: 2025/05/10 17:24:52 by thofstet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_ls(char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
		return ;
	}
	else if (pid == 0)
	{
		char	*args[];
		args[] = {"ls", NULL};
		if (execve("/bin/ls", args, env) == -1)
		{
			perror("execve error frérot");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
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