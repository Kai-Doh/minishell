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
CFLAGS  = -Wall -Wextra -Werror -g -Iinclude -ILibft #-fsanitize=address
LDLIBS  = -lreadline -lhistory -lncurses #-fsanitize=address

# Directories
SRCDIR   = src
OBJDIR   = obj
INCDIR   = include
LIBFTDIR = Libft

# Source files organized by category
CORE_SRCS = $(SRCDIR)/core/minishell.c $(SRCDIR)/core/prompt.c $(SRCDIR)/core/prompt_utils.c $(SRCDIR)/core/signals.c $(SRCDIR)/core/readline_terminal.c

BUILTIN_SRCS = $(SRCDIR)/builtin/dispatcher.c $(SRCDIR)/builtin/echo.c $(SRCDIR)/builtin/pwd.c $(SRCDIR)/builtin/cd.c $(SRCDIR)/builtin/cd_helpers.c $(SRCDIR)/builtin/exit.c $(SRCDIR)/builtin/env.c $(SRCDIR)/builtin/env_utils.c $(SRCDIR)/builtin/env_manager.c $(SRCDIR)/builtin/env_management.c $(SRCDIR)/builtin/export.c $(SRCDIR)/builtin/unset.c

PARSING_SRCS = $(SRCDIR)/parsing/lexer.c $(SRCDIR)/parsing/lexer_token.c $(SRCDIR)/parsing/lexer_utils.c $(SRCDIR)/parsing/parser.c $(SRCDIR)/parsing/parser_cmd.c $(SRCDIR)/parsing/parser_redir.c $(SRCDIR)/parsing/parser_utils.c $(SRCDIR)/parsing/parser_expansion.c $(SRCDIR)/parsing/parser_helpers.c $(SRCDIR)/parsing/syntax_validation.c

EXECUTION_SRCS = $(SRCDIR)/execution/exec.c $(SRCDIR)/execution/exec_utils.c $(SRCDIR)/execution/exec_helpers.c $(SRCDIR)/execution/path.c $(SRCDIR)/execution/redir_utils.c $(SRCDIR)/execution/heredoc.c $(SRCDIR)/execution/heredoc_utils.c $(SRCDIR)/execution/process_wait.c

UTILS_SRCS = $(SRCDIR)/utils/utils.c $(SRCDIR)/utils/path_utils.c $(SRCDIR)/utils/free_cmds.c $(SRCDIR)/utils/input_utils.c $(SRCDIR)/utils/variable_assignment.c $(SRCDIR)/utils/shlvl_utils.c $(SRCDIR)/utils/string_utils.c $(SRCDIR)/utils/wildcard_expansion.c

# All source files
SRCS = $(CORE_SRCS) $(BUILTIN_SRCS) $(PARSING_SRCS) $(EXECUTION_SRCS) $(UTILS_SRCS)

# Object files
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# libft
LIBFT = $(LIBFTDIR)/libft.a

# Rules
all: $(LIBFT) $(NAME)

$(LIBFT):
	@printf "$(BLUE)Building libft...$(RESET)\n"
	@$(MAKE) -C $(LIBFTDIR) bonus
	@printf "$(GREEN)✓ libft built.$(RESET)\n"

# Create object directories
$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/core $(OBJDIR)/builtin $(OBJDIR)/parsing $(OBJDIR)/execution $(OBJDIR)/utils

# Compile source files to object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@printf "$(BLUE)Compiling $<...$(RESET)\n"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	@printf "$(BLUE)Linking $(NAME)...$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDLIBS) -o $(NAME)
	@printf "$(GREEN)✓ $(NAME) created.$(RESET)\n"

clean:
	@printf "$(RED)Cleaning object files...$(RESET)\n"
	@$(RM) -rf $(OBJDIR)
	@$(MAKE) -C $(LIBFTDIR) clean
	@printf "$(GREEN)✓ Objects removed.$(RESET)\n"

fclean: clean
	@printf "$(RED)Removing $(NAME)...$(RESET)\n"
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFTDIR) fclean
	@printf "$(GREEN)✓ Full clean done.$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
