/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_cleanup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 00:00:00 by ktiomico          #+#    #+#             */
/*   Updated: 2025/08/01 00:00:01 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_heredoc_tracking(t_shell *sh)
{
	free(sh->heredoc_fds);
	sh->heredoc_fds = NULL;
	sh->heredoc_count = 0;
}
