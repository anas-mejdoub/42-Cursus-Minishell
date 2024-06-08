SRC = sources/env/env.c sources/env/methods.c sources/minishell.c

OBJ = $(SRC:.c=.o)

LIBFT = sources/super_libft/libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -I includes/

NAME = minishell

RM = rm -rf

all : $(NAME)



$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@${RM} $(OBJ)

fclean : clean
	@${RM} $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re