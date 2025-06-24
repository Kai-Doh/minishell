/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 22:34:30 by ktiomico          #+#    #+#             */
/*   Updated: 2025/04/10 18:13:53 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "./Libft/libft.h"

# define ERROR  1

# define BLACK  "\e[30m"
# define RED    "\e[31m"
# define GREEN  "\e[32m"
# define YELLOW "\e[33m"
# define BLUE   "\e[34m"
# define PURPLE "\e[35m"
# define CYAN   "\e[36m"
# define WHITE  "\e[37m"
# define RESET  "\e[0m"

# define ARGS   "This program does not allow any arguments!"

typedef struct s_data
{
}       t_data;

typedef struct s_cmd
{
    char    **args;
    char    *infile;
    char    *outfile;
}       t_cmd;

int     parse_input(char *line, t_cmd **cmds);
void    free_cmds(t_cmd *cmds, int count);
int     execute_commands(t_cmd *cmds, int count, char **env);
bool    is_builtin(char *cmd);

void    exit_msg(char *msg, int code);
char    *prompt(void);
void    builtin_echo(char *arg);

#endif
