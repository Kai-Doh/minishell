# Colors
RESET = \033[0m
GREEN = \033[32m
BLUE = \033[34m
YELLOW = \033[33m
RED = \033[31m

SRCS =	ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c

SRCS_BONUS =	ft_lstnew_bonus.c \
				ft_lstadd_front_bonus.c \
				ft_lstsize_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstadd_back_bonus.c \
				ft_lstdelone_bonus.c \
				ft_lstclear_bonus.c \
				ft_lstiter_bonus.c \
				ft_lstmap_bonus.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.

RM = rm -rf
AR = ar rc

MAKEFLAGS += --no-print-directory

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: $(OBJS) $(OBJS_BONUS)
	@$(AR) $(NAME) $(OBJS) $(OBJS_BONUS)

clean:
	@$(RM) $(OBJS) $(OBJS_BONUS)
	@echo "$$(echo -e '$(RED)Libft object files removed.$(RESET)')"

fclean: clean
	@$(RM) $(NAME)
	@echo "$$(echo -e '$(GREEN)✔ Library $(NAME) and object files removed.$(RESET)')"

re: fclean all

.PHONY: all clean fclean re bonus
