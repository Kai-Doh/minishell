/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 22:34:30 by ktiomico          #+#    #+#             */
/*   Updated: 2025/05/26 11:58:48 by ktiomico         ###   ########.fr       */
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

typedef struct s_shell
{
	char	**env;
	int		last_exit_status;
}	t_shell;

extern volatile sig_atomic_t	g_signal;

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

void	start_shell_loop(t_shell *sh);

/* ************************************************************************** */
/*                                    Lexer                                   */
/* ************************************************************************** */

t_token	*lexer(char *s, int *error);
char	*extract_token(char *s, int *i, int *error);
int		is_space(char c);
int		is_special(char c);
void	quote_error(int in_s, int *error);
t_type	get_type(char *s);

/* ************************************************************************** */
/*                                    Parser                                  */
/* ************************************************************************** */

t_cmd	*parse(t_token *tok, t_shell *sh);
t_cmd	*add_command(t_token **tok, t_shell *sh);
t_redir	*add_redir(t_token **tok, t_shell *sh);
char	*expand_word(char *s, t_shell *sh);
char	*append_str(char *base, const char *add);
char	*append_char(char *base, char c);
char	*get_env_value(char *name, t_shell *sh);

/* ************************************************************************** */
/*                                    Execution                               */
/* ************************************************************************** */

int		execute(t_cmd *cmd, t_shell *sh);
void	pipe_and_fork(t_cmd *cmd, t_shell *sh, int *in);

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

void	exit_msg(char *msg, int code, t_shell *sh);
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
int		run_builtin(t_cmd *cmd, t_shell *sh);
int		ft_pwd(void);
int		ft_cd(char **args, t_shell *sh);
int		ft_echo(char **args);
int		ft_exit(char **args, t_shell *sh);
int		ft_env(char **env);
int		ft_export(char **args, t_shell *sh);
int		ft_unset(char **args, t_shell *sh);
char	**dup_env(char **env);
char	**ft_strs_add(char **env, char *new_entry);
char	**ft_strs_remove(char **env, int index);
char	**ft_args_add(char **arr, char *new_arg);
char	*strip_comments(char *line);

#endif
