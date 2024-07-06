/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:53:18 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/06 15:48:44 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*new_node(void)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	if (!new)
		return (0);
	new->right = NULL;
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
	new->outfiles = NULL;
	new->type_node = NODE;
	new->args = NULL;
	new->in_files = NULL;
	new->command_arg = NULL;
	new->here_doc = false;
	new->infd = -1;
	new->outfd = -1;
	return (new);
}

void print_2d(t_command *command)
{
	printf("command \t infile \t outfile\n");
	while (command->command_arg)
	{
		printf ("{%s env :{", command->command_arg->content);
		while (command->command_arg->index_list)
		{
			printf(" %d %d,", command->command_arg->index_list->index, command->command_arg->index_list->len);
			command->command_arg->index_list = command->command_arg->index_list->next;
		}
		printf("}}\n");
		command->command_arg = command->command_arg->next;
	}
	printf (" \t");
	while (command->in_files)
	{
		printf("(%s) env : {", command->in_files->filename);
		while (command->in_files->index_list)
		{
			printf("%d %d, ", command->in_files->index_list->index, command->in_files->index_list->len);
			command->in_files->index_list = command->in_files->index_list->next;
		}
		printf("}");
		command->in_files = command->in_files->next;
	}
	printf("\t");
	while (command->outfiles)
	{
		printf("[%s append : %d |{", command->outfiles->filename, (int)command->outfiles->append);
		while (command->outfiles->index_list)
		{
			printf(" %d %d,", command->outfiles->index_list->index, command->outfiles->index_list->len);
			command->outfiles->index_list = command->outfiles->index_list->next;
		}
		printf(" }]");
		command->outfiles = command->outfiles->next;
	}
	printf("\n");
	
}

void	print_tree(t_command *root, int n)
{
	if (!root)
		return ;
	if (root->type_node != NODE)
		printf("root %d\n", root->type_node);
	else if (n == 1)
		printf("----right----\n");
	else if (n == 2)
		printf("----left----\n");
	else
		printf("n is %d this time \n", n);
	if (root->type_node == NODE)
		print_2d(root);
	print_tree(root->right, 1);
	print_tree(root->left, 2);
}

t_command_args *new_arg(char *content, bool env)
{
	t_command_args* new;

	new = malloc (sizeof(t_command_args));
	if (!new)
		return (NULL);
	new->content = content;
	new->env = env;
	new->next = NULL;
	// new->env_arr = NULL;
	new->index_list = NULL;
	return (new);
}

t_command_args *get_last_arg(t_command_args *command)
{
	while (command && command && command->next)
	{
		command = command->next;
	}
	return (command);
}

void add_to_command(t_command *command, t_command_args *new_arg)
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
int set_type_node(int type_elem)
{
	if (type_elem == PIPE_LINE)
		return PIPE_LINE_NODE;
	else if (type_elem == AND)
		return AND_NODE;
	else if (type_elem == OR)
		return OR_NODE;
	return (0);
}
t_command	*handle_pipe_node(t_command *command, int type_elem)
{
	t_command	*pipe_node;

	pipe_node = new_node();
	if (!pipe_node)
		return (NULL);
	
	pipe_node->right = command;
	pipe_node->type_node = set_type_node(type_elem);
	return (pipe_node);
}
t_env_index *new_index(int new, int len)
{
	t_env_index *new_i;
	new_i = malloc(sizeof(t_env_index));
	if (!new_i)
		return NULL;
	new_i->index = new;
	new_i->len = len;
	new_i->expanded = false;
	new_i->next = NULL;
	return (new_i);
}
t_env_index *last_index(t_env_index *list)
{
	while (list && list->next)
	{
		list = list->next;
	}
	return (list);
}
void add_to_index(t_command_args *list, t_env_index *new)
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

int env_index(char *env_str, char *prev)
{
	int i = 0;
	while (env_str && env_str[i])
	{
		if (env_str[i] == '$')
			break;
		i++;
	}
	return (ft_strlen(prev) + i);
}
int *add_int(int *arr, int new)
{
	int i = 0;
	while (arr)
	{
		if (arr[i] == -1)
			break;
		i++;
	}
	int *res = malloc (sizeof (int) * (i + 2));
	if (!res)
		return (NULL);
	int j = 0;
	while (res && j < i)
	{
		res[j] = arr[j];
		j++;
	}
	res[j] = new;
	res[j + 1] = -1;
	return (res);
}
t_command_h_ret *command_handling(t_elem **element)
{
	t_command_h_ret *res;
	res = malloc (sizeof(t_command_h_ret));
	if (!res)
		return (NULL);
	res->command = NULL;
	res->arr = NULL;
	res->env = false;
	res->lens = NULL;
	t_elem *tmp = NULL;
	if ((*element)->type == ENV)
				res->env = true;
	while (*element)
	{
		if ((*element)->type == ENV)
		{
			res->arr = add_int(res->arr, env_index((*element)->content, res->command));
			res->lens = add_int(res->lens, (*element)->len);
			res->env = true;
		}
		if (ft_strchr(" ><|()&", (*element)->type) && (*element)->state == GENERAL && (*element)->type != QOUTE)
		{
			if (ft_strchr("><|()&", (*element)->type))
				*element = tmp;
			return res;
		}
		if (((*element)->state == IN_QUOTE || (*element)->state == IN_DQUOTE) && ((*element)->type != DOUBLE_QUOTE && (*element)->type != QOUTE))
		{
			if (!res->command)
				res->command = (*element)->content;
			else
				res->command = ft_strjoin(res->command, (*element)->content);
		}
		else if ((*element)->state == GENERAL && (*element)->type != QOUTE && (*element)->type != DOUBLE_QUOTE)
		{
			if (!res->command)
				res->command = (*element)->content;
			else
			{
				if ((*element)->type != WHITE_SPACE)
					res->command = ft_strjoin(res->command, (*element)->content);
			}
		}
		tmp = *element;
		*element = (*element)->next;
	}
	if (!res->command)
	{ 
		res->command = ft_strdup("");
	}
	return (res);
}
t_in_files *get_last_in_file(t_in_files *files)
{
	while (files && files->next)
	{
		files = files->next;
	}
	return (files);
}

t_in_files *new_in_file(char *filename, bool here_doc, bool env_qoute)
{
	t_in_files *new;
	new = malloc(sizeof(t_in_files));
	if (!new)
		return (NULL);
	new->filename = filename;
	new->here_doc = here_doc;
	new->in_qoute = env_qoute;
	new->limiter = NULL;
	new->index_list = NULL;
	new->next = NULL;
	if (here_doc)
	{
		
		new->limiter = filename;
	}
	return (new);
}

int my_rand()
{
	static int r;

	if (!r)
		r = 1;
	r *= 50;
    return r % INT_MAX;
}

char *random_str()
{
	char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	char *res = NULL;
	int key;
	int i = 0;
	res = malloc(sizeof (char) * 10);
	if (!res)
		return (NULL);
	while (i < 9)
	{
		int rand = my_rand();
		if (rand < 0)
			rand = -rand;
		key = rand % 61;
		res[i] = charset[key];
		i++;
	}
	res[i] = '\0';
	return (res);
}

void handle_here_doc(t_in_files *file, t_env *env)
{
	char *random = random_str();
	char *file_name = ft_strjoin("/tmp/", random);
	unlink(file_name);
	free(random);
	file->filename = ft_strdup(file_name);
	// printf("filename %s\n", file->filename);
	int i = open(file_name, O_CREAT | O_WRONLY | O_RDONLY , 0777);
	if (i == -1)
	{
		printf("problem with opennig here doc\n");
		return;
	}
	char *str1 = here_doc(file->limiter);
	char *str2 = expand_here_doc_content(str1, env); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	ft_putstr_fd(str2, i);
	close(i);
	// unlink(file_name);
	free(file_name);
}

void add_to_infiles(t_command *command, t_in_files *file, t_env *env)
{
	if (!command->in_files)
	{
		command->in_files = file;
	}
	else
		get_last_in_file(command->in_files)->next = file;
	if (file->here_doc)
		handle_here_doc(file, env);
}

void	handle_redir_in(t_command *command, char *filename, bool env_qoute, t_env *env)
{
	if (command->in_redir)
	{
		add_to_infiles(command, new_in_file(filename, false, env_qoute), env);
	}
	else if (command->here_doc)
	{
		command->here_doc = false;
		add_to_infiles(command, new_in_file(filename, true, env_qoute), env);
	}
}

t_out_files *get_last_file(t_out_files *files)
{
	while (files && files->next)
	{
		files = files->next;
	}
	return (files);
}

t_out_files *new_file(char *filename, bool append, bool env_dqoute)
{
	t_out_files *new;
	new = malloc(sizeof(t_out_files));
	if (!new)
		return (NULL);
	new->filename = filename;
	new->append = append;
	new->in_qoute = env_dqoute;
	new->next = NULL;
	new->index_list = NULL;
	return (new);
}
void add_to_outfiles(t_command *command, t_out_files *file)
{
	if (!command->outfiles)
		command->outfiles = file;
	else
		get_last_file(command->outfiles)->next = file;
}
void	handle_redir_out(t_command *command, char *filename, bool env_dqoute)
{
	command->out_redir = false;
	bool append = false;
	if (command->dredir)
		append = true;
	command->dredir = false;
	add_to_outfiles(command, new_file(filename, append, env_dqoute));
}
void add_indexs_to_args(int *arr, int *lens, t_command_args *args)
{
	int i = 0;
	while (arr)
	{
		if (arr[i] == -1)
			break;
		add_to_index(args, new_index(arr[i], lens[i]) );
		i++;
	}
}
void add_to_out_index(t_out_files *list, t_env_index *new)
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
void add_indexs_to_outfiles(int *arr, int *len, t_out_files *file)
{
	int i = 0;
	while (arr)
	{
		printf ("i is %d\n", i);
		if (arr[i] == -1)
			break;
		
		add_to_out_index(file, new_index(arr[i], len[i]));
		i++;
	}
}

void add_to_in_index(t_in_files *list, t_env_index *new)
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

void add_indexs_to_infiles(int *arr, int *len, t_in_files *file)
{
	int i = 0;
	while (arr)
	{
		printf ("i is %d\n", i);
		if (arr[i] == -1)
			break;
		add_to_in_index(file, new_index(arr[i], len[i]));
		i++;
	}
}
t_command	*parser(t_elem *elements, t_env *env)
{
	t_command	*command;
	t_command	*pipe_node;
	bool		first_time;
	t_command_h_ret *comm_hand_ret;

	comm_hand_ret = NULL;
	first_time = true;
	command = new_node();
	pipe_node = new_node();
	pipe_node->type_node = ROOT_NODE;
	pipe_node->right = command;
	bool env_dqoute = false;
	while (elements)
	{
		// printf("the elem %s\n", elements->content);
		if ((elements->type == WORD || elements->type == ENV) && !command->in_redir && !command->out_redir && !command->dredir && !command->here_doc)
		{
			comm_hand_ret = command_handling(&elements);
			if (comm_hand_ret->env)
			{
				add_to_command(command, new_arg(comm_hand_ret->command, true));
			}
			else
				add_to_command(command, new_arg(comm_hand_ret->command, false));
			add_indexs_to_args(comm_hand_ret->arr, comm_hand_ret->lens, get_last_arg(command->command_arg));
		}
		else if ((elements->type == PIPE_LINE  || elements->type == AND || elements->type == OR ) && first_time == false)
		{
			pipe_node = handle_pipe_node(pipe_node, elements->type);
			if (!pipe_node)
				return (NULL);
			command = new_node();
			pipe_node->left = command;
		}
		else if ((elements->type == PIPE_LINE  || elements->type == AND || elements->type == OR ) && first_time)
		{
			first_time = false;
			command = new_node();
			pipe_node->left = command;
			pipe_node->type_node = set_type_node(elements->type);
		}
		else if (elements->type == REDIR_IN)
			command->in_redir = true;
		else if (elements->type == REDIR_OUT)
			command->out_redir = true;
		else if (elements->type == DREDIR_OUT)
		{
			command->dredir = true;
		}
		else if ((elements->type == WORD || elements->type == ENV || (elements->type == QOUTE &&  ((t_elem *)elements->next) && ((t_elem *)elements->next)->type == QOUTE) || (elements->type == DOUBLE_QUOTE && ((t_elem *)elements->next)  && ((t_elem *)elements->next)->type == DOUBLE_QUOTE)) && (command->out_redir || command->dredir))
		{
			if (elements->state == IN_DQUOTE)
				env_dqoute = true;
			else
				env_dqoute = false;
			comm_hand_ret = command_handling(&elements);
			handle_redir_out(command, comm_hand_ret->command, env_dqoute);
			add_indexs_to_outfiles(comm_hand_ret->arr, comm_hand_ret->lens, get_last_file(command->outfiles));
		}
		else if (elements->type == HERE_DOC)
		{
			command->here_doc = true;
		}
		else if ((elements->type == WORD || elements->type == ENV || (elements->type == QOUTE &&  ((t_elem *)elements->next) && ((t_elem *)elements->next)->type == QOUTE) || (elements->type == DOUBLE_QUOTE && ((t_elem *)elements->next)  && ((t_elem *)elements->next)->type == DOUBLE_QUOTE))  && (command->here_doc || command->in_redir))
		{
			if (elements->state == IN_DQUOTE)
				env_dqoute = true;
			else
				env_dqoute = false;
			comm_hand_ret = command_handling(&elements);
			handle_redir_in(command, comm_hand_ret->command, env_dqoute, env);
			if (command->in_redir)
			{
				command->in_redir = false;
				add_indexs_to_infiles(comm_hand_ret->arr, comm_hand_ret->lens, get_last_in_file(command->in_files));
			}
		}
		else if (elements->type == QOUTE && elements->next && ((t_elem *)elements->next)->type == QOUTE && ((((t_elem *)elements->next)->next && ((t_elem *)((t_elem *)elements->next)->next)->type == WHITE_SPACE) || !((t_elem *)elements->next)->next))
		{
			add_to_command(command, new_arg(ft_strdup(""), false));
		}
		if (elements)
			elements = elements->next;
		else
			break;
	}
	return (pipe_node);
}
