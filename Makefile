SRC =\
		sources/executor/execution/executor.c \
		sources/executor/execution/cmd_exec.c \
		sources/executor/execution/exec_node.c \
		sources/executor/execution/exec_utils.c \
		sources/executor/execution/extra_utils.c \
		sources/executor/execution/paths_args.c \
		sources/executor/execution/pipes.c \
		sources/executor/execution/subshells.c \
		sources/env/env.c sources/env/methods.c sources/env/env_utils.c\
		sources/lexer/lexer.c sources/lexer/lexer_utils.c  sources/lexer/general_tocken_handler.c sources/lexer/qoute_tocken_handler.c sources/lexer/dqoute_tocken_handler.c sources/lexer/syntax_error_utils.c\
		sources/lexer/syntax_error.c \
		sources/parser/parser.c \
		sources/ambiguous/ambiguous_file_creation.c sources/ambiguous/ambiguous_checker.c sources/ambiguous/ambiguous_utils.c sources/ambiguous/ambiguous_utils2.c\
		sources/here_doc/here_doc.c  sources/here_doc/here_doc_expander.c \
		sources/signals/signal.c \
		sources/wildcard/wildcard.c sources/wildcard/fun_wildcard.c\
		sources/helper/env_helper.c sources/helper/print_err.c sources/helper/file_creation.c sources/helper/file_creation_utils.c sources/helper/is_builtin.c sources/helper/env_to_2d_arr.c sources/helper/redirections_helper.c sources/helper/env_pattern.c sources/helper/tockens_checker.c sources/helper/ft_free_join.c\
		sources/executor/builtins/echo.c sources/executor/builtins/pwd.c sources/executor/builtins/env_command.c sources/executor/builtins/exit.c sources/executor/builtins/export.c sources/executor/builtins/cd.c sources/executor/builtins/unset.c\
		sources/minishell.c \
		sources/parser/add_int.c \
		sources/parser/args.c \
		sources/parser/cmd_handler.c \
		sources/parser/conditions.c \
		sources/parser/handle_case.c  \
		sources/parser/in_files.c \
		sources/parser/in_indexes.c \
		sources/parser/indexs.c  \
		sources/parser/node.c \
		sources/parser/out_files.c \
		sources/parser/out_indexes.c \
		sources/parser/parse_here_doc.c \
		sources/parser/parser_utils.c \
		sources/parser/random.c \
		sources/parser/redirs.c \
		sources/parser/subshell.c \
		sources/parser/tree.c 

OBJ = $(SRC:.c=.o)

LIBFT = sources/super_libft/libft.a -L /goinfre/$(USER)/homebrew/opt/readline/lib 

CC = cc

CFLAGS = -Wall -Wextra -Werror -I includes/   -I/goinfre/$(USER)/homebrew/opt/readline/include 

NAME = minishell

RM = rm -rf

all : $(NAME)

$(NAME) : $(OBJ)
	make -C sources/super_libft
	$(CC) $(CFLAGS) -lreadline $(OBJ) $(LIBFT) -o $(NAME)

%.o : %.c ./includes/minishell.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	make clean -C sources/super_libft
	@${RM} $(OBJ)

fclean : clean
	make fclean -C sources/super_libft
	@${RM} $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re