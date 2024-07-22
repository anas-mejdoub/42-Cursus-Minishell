SRC =\
		sources/executor/execution/executor.c \
		sources/env/env.c sources/env/methods.c \
		sources/lexer/lexer.c sources/lexer/lexer_utils.c \
		sources/lexer/syntax_error.c \
		sources/parser/parser.c \
		sources/here_doc/here_doc.c \
		sources/wildcard/wildcard.c \
		sources/helper/env_helper.c sources/helper/file_creation.c sources/helper/free_tree.c sources/helper/is_builtin.c sources/helper/env_to_2d_arr.c sources/helper/redirections_helper.c\
		sources/executor/builtins/echo.c sources/executor/builtins/pwd.c sources/executor/builtins/env_command.c sources/executor/builtins/exit.c sources/executor/builtins/export.c sources/executor/builtins/cd.c sources/executor/builtins/unset.c\
		sources/minishell.c 
		

OBJ = $(SRC:.c=.o)

LIBFT = sources/super_libft/libft.a  -L /goinfre/$(USER)/homebrew/opt/readline/lib 

CC = cc

CFLAGS = -Wall -Wextra -g -I includes/   -I/goinfre/$(USER)/homebrew/opt/readline/include -fsanitize=address

NAME = minishell

RM = rm -rf

all : $(NAME)

$(NAME) : $(OBJ)
	make -C sources/super_libft
	$(CC) $(CFLAGS) -lreadline $(OBJ) $(LIBFT) $(LIBS)  -o $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	make clean -C sources/super_libft
	@${RM} $(OBJ)

fclean : clean
	make fclean -C sources/super_libft
	@${RM} $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re