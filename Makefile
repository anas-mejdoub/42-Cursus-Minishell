SRC =  sources/env/env.c sources/env/methods.c sources/lexer/lexer.c sources/lexer/lexer_utils.c sources/lexer/syntax_error.c sources/parser/parser.c sources/here_doc/here_doc.c sources/minishell.c sources/helper/env_helper.c sources/executor/builtins/echo.c

OBJ = $(SRC:.c=.o)

LIBFT = -L /goinfre/$(USER)/homebrew/opt/readline/lib sources/super_libft/libft.a 

CC = cc

CFLAGS = -Wall -Wextra -g -I includes/ -fsanitize=address -g -I/goinfre/$(USER)/homebrew/opt/readline/include

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