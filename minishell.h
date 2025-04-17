/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 22:34:30 by ktiomico          #+#    #+#             */
/*   Updated: 2025/04/17 13:59:27 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "./Libft/libft.h"

# define ERROR	1

# define BLACK	"\e[30m"
# define RED	"\e[31m"
# define GREEN  "\e[32m"
# define YELLOW "\e[33m"
# define BLUE   "\e[34m"
# define PURPLE "\e[35m"
# define CYAN   "\e[36m"
# define WHITE  "\e[37m"
# define RESET  "\e[0m"

# define ARGS	"ERROR: This program does not allow any arguments!"

typedef enum e_type {
	WORD,
	PIPE,
	END
}	t_type;

typedef struct s_token {
	char			*content;
	t_type		type;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd {
	char			**av;
	struct s_cmd	*next;
}	t_cmd;


void	exit_msg(char *msg, int code);
char	*prompt(void);
t_token *lexer(char *line);
void	ft_tokclear(t_token **lst);
char	**tok_to_argv(t_token *tok, int *argc, t_token **next);
bool	tok_is_builtin_exit(t_token *tok);
int		exec_pipeline(t_token *tok_lst, char **env);
char	*find_cmd_path(char *cmd, char **env);
void	ft_split_free(char **arr);
bool    is_special(char c);
int		ft_isspace(int c);
t_token	*tok_new(char *val, t_type type);
void	tok_add_back(t_token **lst, t_token *new);

#endif
