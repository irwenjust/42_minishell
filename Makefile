NAME = minishell
CFLAGS = -Wextra -Wall -Werror
LIBFT = -L./libft -lft

HEADERS = -I./libft -I./include

SRCS_DIR = src
SRCS =	main.c \
		interface.c \
		signal.c \
		pre_handler/lexer.c \
		pre_handler/token.c \
		pre_handler/expander.c \
		pre_handler/parser.c \
		pre_handler/ast.c \
		pre_handler/handler_utils.c \
		tools/for_ms.c \
		tools/env.c \
		tools/restart.c \
		tools/matrix.c \
		tools/utils.c \
		tools/link_list.c \
		builtins/exit.c 
OBJS = $(addprefix $(SRCS_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

%.o: %.c
	@cc $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

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
