/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thofstet <thofstet>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:01:57 by ktiomico          #+#    #+#             */
/*   Updated: 2025/05/10 17:28:33 by thofstet         ###   ########.fr       */
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

/* ************************************************************************** */
/*                                    Macros                                  */
/* ************************************************************************** */

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

/* ************************************************************************** */
/*                              Structure & Enum                              */
/* ************************************************************************** */

typedef enum e_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	END
}	t_type;

typedef struct s_token
{
	char			*content;
	t_type			type;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_type			type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redir;
	struct s_cmd	*next;
}	t_cmd;



/* ************************************************************************** */
/*                              Prompt + Boucle                               */
/* ************************************************************************** */

void	start_shell_loop(char **env);

/* ************************************************************************** */
/*                                    Lexer                                   */
/* ************************************************************************** */

t_token	*lexer(char *line);
void	free_tokens(t_token *tok);

/* ************************************************************************** */
/*                                    Parser                                  */
/* ************************************************************************** */

t_cmd	*parse(t_token *tok);
void	free_cmds(t_cmd *cmd);

/* ************************************************************************** */
/*                                    Execution                               */
/* ************************************************************************** */

int		execute(t_cmd *cmd, char **env);

/* ************************************************************************** */
/*                                 Redirections                               */
/* ************************************************************************** */

void	handle_redir(t_redir *r);
void	do_redir_in(t_redir *r);
void	do_redir_out(t_redir *r);
void	do_redir_append(t_redir *r);
void	do_heredoc(t_redir *r);

/* ************************************************************************** */
/*                                   HEREDOC                                  */
/* ************************************************************************** */

int		create_heredoc(char *delimiter);

/* ************************************************************************** */
/*                                   PATH                                     */
/* ************************************************************************** */

char	*find_command_path(char *cmd, char **env);
char	*get_path_variable(char **env);
char	*join_path(char *dir, char *cmd);
void	ft_free_split(char **arr);

/* ************************************************************************** */
/*                                   UTILS                                    */
/* ************************************************************************** */

void	exit_msg(char *msg, int code);
void	free_tokens(t_token *tok);
void	free_cmds(t_cmd *cmd);

/* ************************************************************************** */
/*                                   SIGNALS                                  */
/* ************************************************************************** */

void	setup_signals(void);
void	sigint_handler(int sig);

/* ************************************************************************** */
/*                                   BUILTINS                                 */
/* ************************************************************************** */

int		is_builtin(char *cmd);
int		run_builtin(t_cmd *cmd, char **env);
int		ft_pwd(void);
int		ft_cd(char **args, char ***envp);
int		ft_echo(char **args);
int		ft_exit(char **args);

/* ************************************************************************** */
/*                                   ENV	                                 */
/* ************************************************************************** */

void	update_env_var(char ***envp, const char *key, const char *value);
char	**copy_env(char **env);
void	free_env(char **env);

#endif
