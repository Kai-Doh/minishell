# Colors
RESET = \033[0m
GREEN = \033[32m
BLUE = \033[34m
YELLOW = \033[33m
RED = \033[31m

# Executables
MINISHELL = minishell

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
OBJS = $(SRCS:.c=.o)

# Commands
RM = rm -rf

# Directories
LIBFT_DIR = ./Libft
LIBFT = $(LIBFT_DIR)/libft.a

# Targets
all: $(LIBFT) $(MINISHELL)

$(LIBFT):
	@echo "$$(echo -e '$(BLUE)Building libft...$(RESET)')"
	@$(MAKE) -C $(LIBFT_DIR) bonus
	@echo "$$(echo -e '$(GREEN)✔ libft static library created.$(RESET)')"

%.o: %.c
	@echo "$$(echo -e '$(BLUE)Compiling $<...$(RESET)')"
	@$(CC) $(CFLAGS) -c $< -o $@

$(MINISHELL): $(OBJS) $(LIBFT)
	@echo "$$(echo -e '$(BLUE)Linking $(MINISHELL)...$(RESET)')"
	@$(CC) $(OBJS) $(LIBFT) -o $(MINISHELL) $(LDFLAGS)
	@echo "$$(echo -e '$(GREEN)✔ $(MINISHELL) executable created.$(RESET)')"

clean:
	@echo "$$(echo -e '$(RED)Cleaning object files...$(RESET)')"
	@$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "$$(echo -e '$(GREEN)✔ Object files removed.$(RESET)')"

fclean: clean
	@echo "$$(echo -e '$(RED)Removing $(MINISHELL)...$(RESET)')"
	@$(RM) $(MINISHELL)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "$$(echo -e '$(GREEN)✔ $(MINISHELL) removed.$(RESET)')"
	@echo "$$(echo -e '$(GREEN)✔ Full clean complete.$(RESET)')"

re: fclean all

.PHONY: all clean fclean re
