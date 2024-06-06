CC = CC

CFLAGS = -Wall -Wextra -Werror -fsanitize=address

RM = rm -rf

SRC = ./sources/env/*.c

NAME = minishell

OBJ = $(SRC:.c=.o)

INCLUDES = ./includes

make : $(NAME)

$(NAME) : $(OBJ) $(INCLUDES)
	make -C ./sources/super_libft all
	$(CC) $(CFLAGS) $(OBJ) -I INCLUDES -o minishell

%.c : %.o : INCLUDES
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	make -C ./sources/super_libft clean
	@${RM} $(OBJ)

fclean : clean
	make -C ./sources/super_libft fclean
	@${RM} $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re includes sources
