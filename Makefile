# Colours (only used with printf, safe in dash)
RESET  = \033[0m
GREEN  = \033[32m
BLUE   = \033[34m
YELLOW = \033[33m
RED    = \033[31m

# Executable
NAME   = minishell

<<<<<<< HEAD
# Compiler and Flags
CC = gcc
CFLAGS = -Werror -Wall -Wextra -g -I.
LDFLAGS = -lreadline

# Source Files
SRCS =	minishell.c\
		utils.c\
		prompt.c\
		echo.c\

# Object Files (automatiquement générés à partir de SRCS)
=======
# Compiler / flags
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -g -I.
LDLIBS  = -lreadline -lhistory -lncurses   # or -ltermcap

# Sources / objects
SRCS = minishell.c prompt.c exec.c heredoc.c lexer.c parser.c path.c redir_utils.c utils.c signals.c dispatcher.c echo.c pwd.c cd.c exit.c env_utils.c export.c unset.c exec_utils.c lexer_token.c lexer_utils.c parser_utils.c parser_cmd.c free_cmds.c remove_quotes.c env.c
>>>>>>> karl
OBJS = $(SRCS:.c=.o)

# libft
LIBFT_DIR = ./Libft
LIBFT     = $(LIBFT_DIR)/libft.a

# Rules
all: $(LIBFT) $(NAME)

$(LIBFT):
	@printf "$(BLUE)Building libft...$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR) bonus
	@printf "$(GREEN)✓ libft built.$(RESET)\n"

%.o: %.c
	@printf "$(BLUE)Compiling $<...$(RESET)\n"
	@$(CC) $(CFLAGS) -c $< -o $@

<<<<<<< HEAD
$(MINISHELL): $(OBJS) $(LIBFT)
	@echo "$$(echo -e '$(BLUE)Linking $(MINISHELL)...$(RESET)')"
	@$(CC) $(OBJS) $(LIBFT) -o $(MINISHELL) $(LDFLAGS)
	@echo "$$(echo -e '$(GREEN)✔ $(MINISHELL) executable created.$(RESET)')"
=======
$(NAME): $(OBJS) $(LIBFT)
	@printf "$(BLUE)Linking $(NAME)...$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDLIBS) -o $(NAME)
	@printf "$(GREEN)✓ $(NAME) created.$(RESET)\n"
>>>>>>> karl

clean:
	@printf "$(RED)Cleaning object files...$(RESET)\n"
	@$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@printf "$(GREEN)✓ Objects removed.$(RESET)\n"

fclean: clean
	@printf "$(RED)Removing $(NAME)...$(RESET)\n"
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@printf "$(GREEN)✓ Full clean done.$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
