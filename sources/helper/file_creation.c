/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:48:34 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/25 15:30:04 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_helper.h"

// int	count_spaces(char *ptr)
// {
// 	int	i;
// 	int	res;

// 	res = 0;
// 	i = 0;
// 	while (ptr[i])
// 	{
// 		if (ptr[i] == ' ')
// 			res++;
// 		i++;
// 	}
// 	return (res);
// }

// static char	*ambiguous_out_helper(t_env *env, t_out_files *file1)
// {
// 	char	*file_name;

// 	file_name = NULL;
// 	if (file1->index_list || file1->wildcard)
// 		file_name = env_expander(file1->filename, file1->index_list, env,
// 				file1->wildcard);
// 	else
// 		file_name = file1->filename;
// 	if (file1->ambiguous || (ft_strchr(file_name, ' ')
// 			&& count_spaces(file_name) != count_spaces(file1->filename)
// 			&& file1->wildcard))
// 		return (print_err(2, 1, "minishell: : ambiguous redirect\n"), NULL);
// 	return (file_name);
// }

// static char	*ambiguous_in_helper(t_env *env, t_in_files *file2)
// {
// 	char	*file_name;

// 	file_name = NULL;
// 	if (file2->index_list || file2->wildcard)
// 		file_name = env_expander(file2->filename, file2->index_list, env,
// 				file2->wildcard);
// 	else
// 		file_name = file2->filename;
// 	if (file2->ambiguous || (ft_strchr(file_name, ' ')
// 			&& count_spaces(file_name) != count_spaces(file2->filename)
// 			&& file2->wildcard))
// 		return (print_err(2, 1, "minishell: : ambiguous redirect\n"), NULL);
// 	return (file_name);
// }

// char	*ambiguous(void *files, bool type, t_env *env)
// {
// 	t_out_files	*file1;
// 	t_in_files	*file2;

// 	file1 = NULL;
// 	file2 = NULL;
// 	if (type == true)
// 		return (ambiguous_out_helper(env, (t_out_files *)files));
// 	else
// 		return (ambiguous_in_helper(env, (t_in_files *)files));
// }

int	open_file(char *file_name, bool append, bool create, bool type)
{
	if (type == true)
	{
		if (!create && !append)
			return (open(file_name, O_WRONLY | O_TRUNC));
		else if (create && append)
			return (open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0666));
		else if (!create && append)
			return (open(file_name, O_WRONLY | O_APPEND));
		else if (create && !append)
			return (open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666));
	}
	else if (type == false)
		return (open(file_name, O_RDONLY));
	return (-1);
}

static int	helper_open_out_files(char *file_name, t_out_files *files,
		int *last_fd)
{
	if (access(file_name, F_OK) == 0)
	{
		if (access(file_name, W_OK) == 0)
		{
			*last_fd = open_file(file_name, files->append, false, true);
			if (*last_fd == -1)
				return (print_err(6, 1, "minishell : ", file_name, " ",
						strerror(errno), "\n"), -1);
		}
		else
			return (print_err(6, 1, "minishell : ", file_name, " ",
					strerror(errno), "\n"), -1);
	}
	else
	{
		*last_fd = open_file(file_name, files->append, true, true);
		if (*last_fd == -1)
			return (print_err(6, 1, "minishell : ", file_name, " ",
					strerror(errno), "\n"), -1);
	}
	return (0);
}

int	open_out_files(t_out_files *files, t_env *env)
{
	int		last_fd;
	char	*file_name;

	last_fd = 0;
	while (files)
	{
		file_name = ambiguous(files, true, env);
		if (file_name == NULL)
			return (-1);
		if (helper_open_out_files(file_name, files, &last_fd) == -1)
			return (-1);
		if (files->next)
			close(last_fd);
		files = files->next;
	}
	return (last_fd);
}

static int	helper_open_in_files(char *file_name, int *last_fd)
{
	if (access(file_name, F_OK) == 0)
	{
		if (access(file_name, R_OK) == 0)
		{
			*last_fd = open_file(file_name, false, false, false);
			if (*last_fd == -1)
				return (print_err(6, 1, "minishell : ", file_name, " ",
						strerror(errno), "\n"), -1);
		}
		else
			return (print_err(6, 1, "minishell : ", file_name, " ",
					strerror(errno), "\n"), -1);
	}
	else
		return (print_err(6, 1, "minishell : ", file_name, " ", strerror(errno),
				"\n"), -1);
	return (0);
}

int	open_in_files(t_in_files *files, t_env *env)
{
	int		last_fd;
	char	*file_name;

	last_fd = 0;
	while (files)
	{
		file_name = ambiguous(files, false, env);
		if (file_name == NULL)
			return (-1);
		if (helper_open_in_files(file_name, &last_fd) == -1)
			return (-1);
		if (files->next)
			close(last_fd);
		files = files->next;
	}
	return (last_fd);
}
