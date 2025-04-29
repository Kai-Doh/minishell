# Colours (only used with printf, safe in dash)
RESET  = \033[0m
GREEN  = \033[32m
BLUE   = \033[34m
YELLOW = \033[33m
RED    = \033[31m

# Executable
NAME   = minishell

# Compiler / flags
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -g -I.
LDLIBS  = -lreadline -lhistory -lncurses   # or -ltermcap

# Sources / objects
SRCS = minishell.c prompt.c exec.c heredoc.c lexer.c parser.c path.c redir_utils.c utils.c signals.c
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

$(NAME): $(OBJS) $(LIBFT)
	@printf "$(BLUE)Linking $(NAME)...$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDLIBS) -o $(NAME)
	@printf "$(GREEN)✓ $(NAME) created.$(RESET)\n"

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
