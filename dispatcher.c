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
	return (!ft_strncmp(cmd, "echo", 5)
		|| !ft_strncmp(cmd, "cd", 3)
		|| !ft_strncmp(cmd, "pwd", 4)
		|| !ft_strncmp(cmd, "exit", 5)
		|| !ft_strncmp(cmd, "env", 4)
		|| !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "unset", 6));
}

int             run_builtin(t_cmd *cmd, t_shell *sh)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (!ft_strncmp(cmd->args[0], "echo", 5))
		return (ft_echo(cmd->args));
	if (!ft_strncmp(cmd->args[0], "cd", 3))
		return (ft_cd(cmd->args, sh->env));
	if (!ft_strncmp(cmd->args[0], "pwd", 4))
		return (ft_pwd());
	if (!ft_strncmp(cmd->args[0], "exit", 5))
		return (ft_exit(cmd->args, sh));
	if (!ft_strncmp(cmd->args[0], "env", 4))
		return (ft_env(sh->env));
	if (!ft_strncmp(cmd->args[0], "export", 7))
		return (ft_export(cmd->args, sh));
	if (!ft_strncmp(cmd->args[0], "unset", 6))
		return (ft_unset(cmd->args, sh));
	return (1);
}
