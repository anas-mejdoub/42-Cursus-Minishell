/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:53:18 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/24 09:55:09 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*wild_card_handler(t_command_h_ret *res)
{
	char	a[2];

	a[0] = -17;
	a[1] = '\0';
	res->wildcard = true;
	return (ft_strdup(a));
}

int	allocate_node1(t_elem **elem, char *content, int state, int token)
{
	t_elem	*new_node;
	t_elem	*last_node;

	if (!content || content[0] == '\0')
		return (0);
	new_node = malloc(sizeof(t_elem));
	if (!new_node)
		return (1);
	new_node->state = state;
	new_node->type = token;
	new_node->content = content;
	new_node->len = ft_strlen(content);
	new_node->next = NULL;
	if (!(*elem))
		(*elem) = new_node;
	else
	{
		last_node = *elem;
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = new_node;
	}
	return (0);
}

void	intialize_new_node(t_command *new)
{
	new->right = NULL;
	new->fd[0] = -1;
	new->fd[1] = -1;
	new->to_close = NULL;
	new->left = NULL;
	new->path = NULL;
	new->pipe = false;
	new->and_ = false;
	new->or_ = false;
	new->builtin = false;
	new->infile = NULL;
	new->outfile = NULL;
	new->in_redir = false;
	new->out_redir = false;
	new->dredir = false;
	new->dup = false;
	new->outfiles = NULL;
	new->type_node = NODE;
	new->args = NULL;
	new->in_files = NULL;
	new->command_arg = NULL;
	new->here_doc = false;
	new->infd = -1;
	new->outfd = -1;
}

t_command	*new_node(void)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	if (!new)
		return (0);
	intialize_new_node(new);
	return (new);
}

// void	print_2d(t_command *command)
// {
// 	printf("command \t infile \t outfile\n");
// 	while (command->command_arg)
// 	{
// 		printf("{%s env :{", command->command_arg->content);
// 		while (command->command_arg->index_list)
// 		{
// 			printf(" %d %d,", command->command_arg->index_list->index,
// 				command->command_arg->index_list->len);
// 			command->command_arg->index_list = command->command_arg->index_list->next;
// 		}
// 		printf("}}\n");
// 		command->command_arg = command->command_arg->next;
// 	}
// 	printf(" \t");
// 	while (command->in_files)
// 	{
// 		printf("(%s) env : {", command->in_files->filename);
// 		while (command->in_files->index_list)
// 		{
// 			printf("%d %d, ", command->in_files->index_list->index,
// 				command->in_files->index_list->len);
// 			command->in_files->index_list = command->in_files->index_list->next;
// 		}
// 		printf("}");
// 		command->in_files = command->in_files->next;
// 	}
// 	printf("\t");
// 	while (command->outfiles)
// 	{
// 		printf("[%s append : %d |{", command->outfiles->filename,
// 			(int)command->outfiles->append);
// 		while (command->outfiles->index_list)
// 		{
// 			printf(" %d %d,", command->outfiles->index_list->index,
// 				command->outfiles->index_list->len);
// 			command->outfiles->index_list = command->outfiles->index_list->next;
// 		}
// 		printf(" }]");
// 		command->outfiles = command->outfiles->next;
// 	}
// 	printf("\n");
// }

// void	print_tree(t_command *root, int n)
// {
// 	if (!root)
// 		return ;
// 	// if (root->type_node != NODE)
// 	// if (root->type_node == NODE)
// 	// 	printf("simple node \n");
// 	printf("START\n");
// 	// if (root->type_node == SUBSHELL_NODE)
// 	// 	printf("subshell opened\n");
// 	if (root->type_node == PIPE_LINE_NODE)
// 		printf("PIPE LINE node\n");
// 	if (root->type_node == AND_NODE)
// 		printf("AND node\n");
// 	if (root->type_node == OR_NODE)
// 		printf("OR node\n");
// 	if (root->type_node == SUBSHELL_NODE)
// 		printf("SUBSHELL_NODE\n");
// 	// printf("type of node %d\n", root->type_node);
// 	if (n == 1)
// 		printf("----right----\n");
// 	if (n == 2)
// 		printf("----left----\n");
// 	// else
// 	// 	printf("n is %d this time \n", n);
// 	// if (root->type_node == NODE || root->type_node == SUBSHELL_NODE)
// 	print_2d(root);
// 	printf("END\n");
// 	print_tree(root->right, 1);
// 	print_tree(root->left, 2);
// }

t_command_args	*new_arg(char *content, bool including_null, bool wild_card,
		bool env)
{
	t_command_args	*new;

	new = malloc(sizeof(t_command_args));
	if (!new)
		return (NULL);
	new->content = content;
	new->env = env;
	new->wildcard = wild_card;
	new->including_null = including_null;
	new->next = NULL;
	new->index_list = NULL;
	return (new);
}

t_command_args	*get_last_arg(t_command_args *command)
{
	while (command && command && command->next)
	{
		command = command->next;
	}
	return (command);
}

void	add_to_command(t_command *command, t_command_args *new_arg)
{
	if (!(command->command_arg))
	{
		command->command_arg = new_arg;
	}
	else
	{
		get_last_arg(command->command_arg)->next = new_arg;
	}
}
void	free2d(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	**add_to_args(char **args, char *to_append)
{
	int		i;
	char	**new;

	i = 0;
	while (args && args[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (args && args[i])
	{
		new[i] = ft_strdup(args[i]);
		i++;
	}
	new[i] = ft_strdup(to_append);
	new[i + 1] = NULL;
	free2d(args);
	return (new);
}
int	set_type_node(int type_elem)
{
	if (type_elem == PIPE_LINE)
		return (PIPE_LINE_NODE);
	else if (type_elem == AND)
		return (AND_NODE);
	else if (type_elem == OR)
		return (OR_NODE);
	else if (type_elem == START_SUBSHELL)
		return (SUBSHELL_NODE);
	return (0);
}
t_command	*handle_pipe_node(t_command *command, int type_elem)
{
	t_command	*pipe_node;

	pipe_node = new_node();
	if (!pipe_node)
		return (NULL);
	pipe_node->right = command;
	pipe_node->left = NULL;
	pipe_node->type_node = set_type_node(type_elem);
	return (pipe_node);
}
t_env_index	*new_index(int new, int len)
{
	t_env_index	*new_i;

	new_i = malloc(sizeof(t_env_index));
	if (!new_i)
		return (NULL);
	new_i->index = new;
	new_i->len = len;
	new_i->expanded = false;
	new_i->next = NULL;
	return (new_i);
}
t_env_index	*last_index(t_env_index *list)
{
	while (list && list->next)
	{
		list = list->next;
	}
	return (list);
}
void	add_to_index(t_command_args *list, t_env_index *new)
{
	if (!list->index_list)
	{
		list->index_list = new;
	}
	else
	{
		last_index(list->index_list)->next = new;
	}
}

int	env_index(char *env_str, char *prev)
{
	int	i;

	i = 0;
	while (env_str && env_str[i])
	{
		if (env_str[i] == '$')
			break ;
		i++;
	}
	return (ft_strlen(prev) + i);
}
int	*add_int(int *arr, int new)
{
	int	i;
	int	*res;
	int	j;

	i = 0;
	while (arr)
	{
		if (arr[i] == -1)
			break ;
		i++;
	}
	res = malloc(sizeof(int) * (i + 2));
	if (!res)
		return (NULL);
	j = 0;
	while (res && j < i)
	{
		res[j] = arr[j];
		j++;
	}
	res[j] = new;
	res[j + 1] = -1;
	return (res);
}
void	handle_general_case(t_elem **element, t_command_h_ret *res)
{
	if (!res->command)
	{
		if ((*element)->type == WILDCARD)
			res->command = wild_card_handler(res);
		else
			res->command = (*element)->content;
	}
	else
	{
		if ((*element)->type != WHITE_SPACE)
		{
			if ((*element)->type == WILDCARD)
			{
				res->command = ft_strjoin(res->command, wild_card_handler(res));
			}
			else
				res->command = ft_strjoin(res->command, (*element)->content);
		}
	}
}
void	handle_env_case(t_elem **element, t_command_h_ret *res)
{
	res->arr = add_int(res->arr, env_index((*element)->content, res->command));
	res->lens = add_int(res->lens, (*element)->len);
	res->env = true;
}
t_command_h_ret	*intialize_ret_cmd(void)
{
	t_command_h_ret	*res;

	res = malloc(sizeof(t_command_h_ret));
	if (!res)
		return (NULL);
	res->command = NULL;
	res->arr = NULL;
	res->wildcard = false;
	res->env = false;
	res->lens = NULL;
	res->including_null = false;
	return (res);
}

void	handle_empty_quote(t_command_h_ret *res)
{
	if (!res->command)
		res->command = ft_strdup("");
}
void	handle_quotes_case(t_elem **element, t_command_h_ret *res)
{
	if (!res->command)
		res->command = (*element)->content;
	else
		res->command = ft_strjoin(res->command, (*element)->content);
}

void	command_handl_core(t_elem **element, t_command_h_ret *res)
{
	if (((*element)->type == QOUTE && (*element)->next
			&& ((t_elem *)(*element)->next)->type == QOUTE)
		|| ((*element)->type == DOUBLE_QUOTE && (*element)->next
			&& ((t_elem *)(*element)->next)->type == DOUBLE_QUOTE))
		handle_empty_quote(res);
	if ((*element)->type == DOUBLE_QUOTE || (*element)->type == QOUTE)
		res->including_null = true;
	if ((*element)->type == ENV)
		handle_env_case(element, res);
	if (((*element)->state == IN_QUOTE || (*element)->state == IN_DQUOTE)
		&& ((*element)->type != DOUBLE_QUOTE && (*element)->type != QOUTE))
		handle_quotes_case(element, res);
	else if ((*element)->state == GENERAL && (*element)->type != QOUTE
		&& (*element)->type != DOUBLE_QUOTE)
		handle_general_case(element, res);
}

t_command_h_ret	*command_handling(t_elem **element)
{
	t_command_h_ret	*res;
	t_elem			*tmp;

	res = intialize_ret_cmd();
	tmp = NULL;
	if ((*element)->type == ENV)
		res->env = true;
	while (*element)
	{
		command_handl_core(element, res);
		if (ft_strchr(" ><|()&", (*element)->type)
			&& (*element)->state == GENERAL && (*element)->type != QOUTE)
		{
			if (ft_strchr("><|()&", (*element)->type))
				*element = tmp;
			return (res);
		}
		tmp = *element;
		*element = (*element)->next;
	}
	if (!res->command)
		res->command = ft_strdup("");
	return (res);
}
t_in_files	*get_last_in_file(t_in_files *files)
{
	while (files && files->next)
	{
		files = files->next;
	}
	return (files);
}

t_in_files	*new_in_file(char *filename, bool here_doc, bool env_qoute,
		bool wild_card)
{
	t_in_files	*new;

	new = malloc(sizeof(t_in_files));
	if (!new)
		return (NULL);
	new->filename = filename;
	new->here_doc = here_doc;
	new->ambiguous = env_qoute;
	new->limiter = NULL;
	new->wildcard = wild_card;
	new->index_list = NULL;
	new->next = NULL;
	if (here_doc)
	{
		new->limiter = filename;
	}
	return (new);
}

int	my_rand(void)
{
	static int	r;

	if (!r)
		r = 1;
	r *= 50;
	return (r % INT_MAX);
}

char	*random_str(void)
{
	char	charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	char	*res;
	int		key;
	int		i;
	int		rand;

	res = NULL;
	i = 0;
	res = malloc(sizeof(char) * 10);
	if (!res)
		return (NULL);
	while (i < 9)
	{
		rand = my_rand();
		if (rand < 0)
			rand = -rand;
		key = rand % 61;
		res[i] = charset[key];
		i++;
	}
	res[i] = '\0';
	return (res);
}

int	handle_here_doc(t_in_files *file, t_env *env)
{
	char	*random;
	char	*file_name;
	int		i;
	char	*str1;
	char	*str2;

	random = random_str();
	file_name = ft_strjoin("/tmp/", random);
	unlink(file_name);
	free(random);
	file->filename = ft_strdup(file_name);
	i = open(file_name, O_CREAT | O_WRONLY | O_RDONLY, 0777);
	if (i == -1)
	{
		ft_putstr_fd("problem with opennig here doc\n", 2);
		return (-1);
	}
	str1 = here_doc(file->limiter);
	if (str1 == NULL)
		return (-1);
	str2 = expand_here_doc_content(str1, env);
	ft_putstr_fd(str2, i);
	close(i);
	free(file_name);
	return (0);
}

int	add_to_infiles(t_command *command, t_in_files *file, t_env *env)
{
	if (!command->in_files)
	{
		command->in_files = file;
	}
	else
		get_last_in_file(command->in_files)->next = file;
	if (file->here_doc)
	{
		if (handle_here_doc(file, env) == -1)
			return (-1);
	}
	return (0);
}

int	handle_redir_in(t_command *command, char *filename, bool env_qoute,
		t_env *env, bool wild_card)
{
	if (command->in_redir)
	{
		add_to_infiles(command, new_in_file(filename, false, env_qoute,
				wild_card), env);
	}
	else if (command->here_doc)
	{
		command->here_doc = false;
		return (add_to_infiles(command, new_in_file(filename, true, env_qoute,
					wild_card), env));
	}
	return (0);
}

t_out_files	*get_last_file(t_out_files *files)
{
	while (files && files->next)
	{
		files = files->next;
	}
	return (files);
}

t_out_files	*new_file(char *filename, bool append, bool ambiguous,
		bool wild_card)
{
	t_out_files	*new;

	new = malloc(sizeof(t_out_files));
	if (!new)
		return (NULL);
	new->filename = filename;
	new->append = append;
	new->ambiguous = ambiguous;
	new->wildcard = wild_card;
	new->next = NULL;
	new->index_list = NULL;
	return (new);
}
void	add_to_outfiles(t_command *command, t_out_files *file)
{
	if (!command->outfiles)
		command->outfiles = file;
	else
		get_last_file(command->outfiles)->next = file;
}
void	handle_redir_out(t_command *command, char *filename, bool ambiguous,
		bool wild_card)
{
	bool	append;

	command->out_redir = false;
	append = false;
	if (command->dredir)
		append = true;
	command->dredir = false;
	add_to_outfiles(command, new_file(filename, append, ambiguous, wild_card));
}
void	add_indexs_to_args(int *arr, int *lens, t_command_args *args)
{
	int	i;

	i = 0;
	while (arr)
	{
		if (arr[i] == -1)
			break ;
		add_to_index(args, new_index(arr[i], lens[i]));
		i++;
	}
}
void	add_to_out_index(t_out_files *list, t_env_index *new)
{
	if (!list->index_list)
	{
		list->index_list = new;
	}
	else
	{
		last_index(list->index_list)->next = new;
	}
}
void	add_indexs_to_outfiles(int *arr, int *len, t_out_files *file)
{
	int	i;

	i = 0;
	while (arr)
	{
		// printf ("i is %d\n", i);
		if (arr[i] == -1)
			break ;
		add_to_out_index(file, new_index(arr[i], len[i]));
		i++;
	}
}

void	add_to_in_index(t_in_files *list, t_env_index *new)
{
	if (!list->index_list)
	{
		list->index_list = new;
	}
	else
	{
		last_index(list->index_list)->next = new;
	}
}

void	add_indexs_to_infiles(int *arr, int *len, t_in_files *file)
{
	int	i;

	i = 0;
	while (arr)
	{
		// printf ("i is %d\n", i);
		if (arr[i] == -1)
			break ;
		add_to_in_index(file, new_index(arr[i], len[i]));
		i++;
	}
}
void	print_node(t_elem *el)
{
	printf("start of set\n");
	while (el)
	{
		printf("elem %s\n", el->content);
		el = el->next;
	}
	printf("end of set\n");
}
int	get_rank(int n)
{
	if (n == PIPE_LINE)
		return (P);
	if (n == AND)
		return (A);
	if (n == OR)
		return (O);
	return (0);
}

bool	handle_subshell(t_command *command, t_elem **elements, t_env *env)
{
	t_command	*tmp;
	int			lvl;
	t_elem		*subshell_set;

	tmp = NULL;
	lvl = 0;
	subshell_set = NULL;
	while (*elements != NULL)
	{
		if ((*elements)->type == END_SUBSHELL && lvl == 0)
		{
			elements = (*elements)->next;
			break ;
		}
		if ((*elements)->type == START_SUBSHELL)
			lvl++;
		if ((*elements)->type == END_SUBSHELL)
			lvl--;
		allocate_node1(&subshell_set, (*elements)->content, (*elements)->state,
			(*elements)->type);
		*elements = (*elements)->next;
	}
	command->type_node = SUBSHELL_NODE;
	tmp = parser(subshell_set, env);
	if (!tmp)
		return (false);
	if (tmp->type_node == ROOT_NODE)
	{
		if (((t_command *)tmp->right)->type_node != ROOT_NODE)
			tmp = tmp->right;
	}
	command->right = tmp;
	return (true);
}

int	split_tree(t_elem *elements, t_command **command, t_command **pipe_node,
		int *r)
{
	if (get_rank(elements->type) >= *r)
	{
		*pipe_node = handle_pipe_node(*pipe_node, elements->type);
		if (!*pipe_node)
			return (0);
		*command = new_node();
		(*pipe_node)->left = *command;
		*r = get_rank(elements->type);
	}
	else
	{
		*command = handle_pipe_node(*command, elements->type);
		(*pipe_node)->left = handle_pipe_node((*pipe_node)->left,
				elements->type);
		(*command)->left = new_node();
		*command = (*command)->left;
		((t_command *)(*pipe_node)->left)->left = *command;
	}
	return (0);
}

int	first_split_tree(t_elem *elements, t_command **command,
		t_command **pipe_node, bool *f)
{
	int	r;

	r = 0;
	if (elements->type == PIPE_LINE)
		r = P;
	if (elements->type == AND)
		r = A;
	if (elements->type == OR)
		r = O;
	*f = false;
	*command = new_node();
	(*pipe_node)->left = *command;
	(*pipe_node)->type_node = set_type_node(elements->type);
	return (r);
}

void	redir_out_parse(t_elem **elements, t_command **command, t_env *env)
{
	t_command_h_ret	*comm_hand_ret;
	t_elem			*tmp;

	tmp = *elements;
	comm_hand_ret = command_handling(elements);
	handle_redir_out(*command, comm_hand_ret->command, imbg(tmp, env),
		comm_hand_ret->wildcard);
	add_indexs_to_outfiles(comm_hand_ret->arr, comm_hand_ret->lens,
		get_last_file((*command)->outfiles));
}
bool	redir_in_parse(t_elem **elements, t_command **command, t_env *env)
{
	t_command_h_ret	*comm_hand_ret;
	t_elem			*tmp;

	tmp = *elements;
	comm_hand_ret = command_handling(elements);
	if (handle_redir_in(*command, comm_hand_ret->command, imbg(tmp, env), env,
			comm_hand_ret->wildcard) == -1)
	{
		globalVar = 1;
		return (false);
	}
	if ((*command)->in_redir)
	{
		(*command)->in_redir = false;
		add_indexs_to_infiles(comm_hand_ret->arr, comm_hand_ret->lens,
			get_last_in_file((*command)->in_files));
	}
	return (true);
}

void	command_args_parse(t_elem **elements, t_command **command)
{
	t_command_h_ret	*comm_hand_ret;

	comm_hand_ret = command_handling(elements);
	if (comm_hand_ret->env)
		add_to_command(*command, new_arg(comm_hand_ret->command,
				comm_hand_ret->including_null, comm_hand_ret->wildcard, true));
	else
		add_to_command(*command, new_arg(comm_hand_ret->command,
				comm_hand_ret->including_null, comm_hand_ret->wildcard, false));
	add_indexs_to_args(comm_hand_ret->arr, comm_hand_ret->lens,
		get_last_arg((*command)->command_arg));
}
bool	redir_out_condition(t_elem *elements, t_command *command)
{
	if (elements && ((elements->type == WORD || elements->type == WILDCARD
				|| elements->type == ENV || (elements->type == QOUTE
					&& elements->next
					&& ((t_elem *)elements->next)->type == QOUTE)
				|| (elements->type == DOUBLE_QUOTE && elements->next
					&& ((t_elem *)elements->next)->type == DOUBLE_QUOTE))
			&& (command->out_redir || command->dredir)))
	{
		return (true);
	}
	return (false);
}

bool	redir_in_condition(t_elem *elements, t_command *command)
{
	if (elements && ((elements->type == WORD || elements->type == WILDCARD
				|| elements->type == ENV || (elements->type == QOUTE
					&& elements->next
					&& ((t_elem *)elements->next)->type == QOUTE)
				|| (elements->type == DOUBLE_QUOTE && elements->next
					&& ((t_elem *)elements->next)->type == DOUBLE_QUOTE))
			&& (command->in_redir || command->here_doc)))
	{
		return (true);
	}
	return (false);
}
void	intialize_parser(t_command **command, t_command **pipe_node, bool *f,
		int *r)
{
	*command = new_node();
	*pipe_node = new_node();
	(*pipe_node)->type_node = ROOT_NODE;
	(*pipe_node)->right = *command;
	*r = 0;
	*f = true;
}

bool	args_parse_condit(t_elem *elements, t_command *command)
{
	if ((elements->type == WORD || elements->type == WILDCARD
			|| elements->type == ENV || elements->type == QOUTE
			|| elements->type == DOUBLE_QUOTE) && !command->in_redir
		&& !command->out_redir && !command->dredir && !command->here_doc)
	{
		return (true);
	}
	return (false);
}

bool	parser_redirs_switch(t_elem **elem, t_command **cmd, t_env *env)
{
	if (elem && (*elem)->type == REDIR_IN)
		(*cmd)->in_redir = true;
	else if (elem && (*elem)->type == REDIR_OUT)
		(*cmd)->out_redir = true;
	else if (elem && (*elem)->type == DREDIR_OUT)
		(*cmd)->dredir = true;
	else if (redir_out_condition(*elem, *cmd))
		redir_out_parse(elem, cmd, env);
	else if (elem && (*elem)->type == HERE_DOC)
		(*cmd)->here_doc = true;
	else if (redir_in_condition(*elem, *cmd))
		if (!redir_in_parse(elem, cmd, env))
			return (false);
	return (true);
}

bool	subshell_container(t_elem **elem, t_command **cmd, t_env *env)
{
	*elem = (*elem)->next;
	if (!handle_subshell(*cmd, elem, env))
		return (false);
	return (true);
}
bool	command_args_condition(t_elem *elements, t_command *command)
{
	if ((elements->type == WORD || elements->type == WILDCARD
			|| elements->type == ENV || elements->type == QOUTE
			|| elements->type == DOUBLE_QUOTE) && !command->in_redir
		&& !command->out_redir && !command->dredir && !command->here_doc)
		return (true);
	return (false);
}

bool	split_tree_cond(t_elem *elements, bool ft)
{
	if (elements && (elements->type == PIPE_LINE || elements->type == AND
			|| elements->type == OR) && ft == false)
		return (true);
	return (false);
}
bool	f_split_tree_cond(t_elem *elements, bool ft)
{
	if (elements && (elements->type == PIPE_LINE || elements->type == AND
			|| elements->type == OR) && ft == true)
		return (true);
	return (false);
}

t_command	*parser(t_elem *elements, t_env *env)
{
	t_command	*command;
	t_command	*pipe_node;
	bool		ft;
	int			r;

	intialize_parser(&command, &pipe_node, &ft, &r);
	while (elements)
	{
		if (elements && elements->type == START_SUBSHELL
			&& !subshell_container(&elements, &command, env))
			return (NULL);
		else if (command_args_condition(elements, command))
			command_args_parse(&elements, &command);
		else if (split_tree_cond(elements, ft))
			split_tree(elements, &command, &pipe_node, &r);
		else if (f_split_tree_cond(elements, ft))
			r = first_split_tree(elements, &command, &pipe_node, &ft);
		else if (!parser_redirs_switch(&elements, &command, env))
			return (NULL);
		if (elements)
			elements = elements->next;
		else
			break ;
	}
	return (pipe_node);
}
