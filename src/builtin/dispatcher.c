/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:37:41 by ktiomico          #+#    #+#             */
/*   Updated: 2025/05/26 12:04:50 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "echo", 4) && cmd[4] == '\0')
		return (1);
	if (!ft_strncmp(cmd, "cd", 2) && cmd[2] == '\0')
		return (1);
	if (!ft_strncmp(cmd, "pwd", 3) && cmd[3] == '\0')
		return (1);
	if (!ft_strncmp(cmd, "exit", 4) && cmd[4] == '\0')
		return (1);
	if (!ft_strncmp(cmd, "env", 3) && cmd[3] == '\0')
		return (1);
	if (!ft_strncmp(cmd, "export", 6) && cmd[6] == '\0')
		return (1);
	if (!ft_strncmp(cmd, "unset", 5) && cmd[5] == '\0')
		return (1);
	return (0);
}

int	run_builtin(t_cmd *cmd, t_shell *sh)
{
	char	*name;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	name = cmd->args[0];
	if (!ft_strncmp(name, "echo", 4) && name[4] == '\0')
		return (ft_echo(cmd->args));
	if (!ft_strncmp(name, "cd", 2) && name[2] == '\0')
		return (ft_cd(cmd->args, sh));
	if (!ft_strncmp(name, "pwd", 3) && name[3] == '\0')
		return (ft_pwd());
	if (!ft_strncmp(name, "exit", 4) && name[4] == '\0')
		return (ft_exit(cmd->args, sh));
	if (!ft_strncmp(name, "env", 3) && name[3] == '\0')
		return (ft_env(sh->env));
	if (!ft_strncmp(name, "export", 6) && name[6] == '\0')
		return (ft_export(cmd->args, sh));
	if (!ft_strncmp(name, "unset", 5) && name[5] == '\0')
		return (ft_unset(cmd->args, sh));
	return (1);
}
