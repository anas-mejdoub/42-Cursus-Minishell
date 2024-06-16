SRC = sources/env/env.c sources/env/methods.c sources/minishell.c sources/lexer/lexer.c sources/lexer/lexer_utils.c sources/parser/parser.c

OBJ = $(SRC:.c=.o)

LIBFT = sources/super_libft/libft.a

CC = cc

CFLAGS = -Wall -Wextra   -g -I includes/ -fsanitize=address -g

NAME = minishell

RM = rm -rf

all : $(NAME)

$(NAME) : $(OBJ)
	make -C sources/super_libft
	$(CC) $(CFLAGS) -lreadline $(OBJ) $(LIBFT) -o $(NAME)

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