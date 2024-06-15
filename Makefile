SRC = sources/env/env.c sources/env/methods.c sources/minishell.c sources/lexer/lexer.c sources/lexer/lexer_utils.c

OBJ = $(SRC:.c=.o)

LIBFT = sources/super_libft/libft.a

CC = cc

CFLAGS = -Wall -Wextra  -fsanitize=address -g -I includes/

NAME = minishell

RM = rm -rf

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -lreadline $(OBJ) $(LIBFT) -o $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@${RM} $(OBJ)

fclean : clean
	@${RM} $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re