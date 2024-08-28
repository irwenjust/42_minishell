NAME = minishell
CFLAGS = -Wextra -Wall -Werror
LIBFT = -L./libft -lft

SRCS =	src/main.c \
		src/interface.c \
		src/tools/for_ms.c \
		src/tools/env.c \
		src/tools/clean.c \
		src/tools/matrix.c \
		src/tools/utils.c 

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	@cc $(CFLAGS) -o $@ -c $< && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@$(MAKE) -C ./libft
	@cc $(OBJS) $(LIBFT) -o $(NAME) -lreadline

clean:
	@rm -rf $(OBJS)
	@$(MAKE) -C ./libft clean

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -C ./libft fclean

re: clean all

.PHONY: all clean fclean re
