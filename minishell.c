/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:42:20 by ktiomico          #+#    #+#             */
/*   Updated: 2025/04/10 14:06:51 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
    char *rl;
	while (1)
	{
    	rl = readline(GREEN "Minishell > " RESET);
    	printf("%s\n", rl);
		if (ft_strncmp(rl, "exit", 4) == 0)
    		return (0);
	}
}
