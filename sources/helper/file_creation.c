/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:48:34 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/29 07:43:21 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_helper.h"

int change_content(t_in_files *file, t_env *env)
{
	char *ptr;
	char *ptr2;
	char buffer[1024];
	int readbyte;
	int fd;

	readbyte = 0;
	fd = open(file->filename, O_RDONLY);
	if (fd < 1)
		return (print_err(2, 1, "error while opening heredoc file") ,-1);
	ptr = ft_alloc(1, NULL, CALLOC);
	while (1)
	{
		readbyte = read(fd, buffer, 1024);
		if (readbyte < 0)
			return (print_err(2, 1, "error while reading heredoc file") ,-1);
		if (readbyte == 0)
			break;
		buffer[readbyte] = '\0';
		ptr = ft_freed_join(ptr, buffer);
	}
	close(fd);
	ptr2 = expand_here_doc_content(ptr, env);
	ft_alloc(0, ptr, FREE_PTR);
	fd = open(file->filename, O_WRONLY | O_TRUNC);
	if (fd < 0)
		return (print_err(2, 1, "error while writing in heredoc file") ,-1);
	write(fd, ptr2, ft_strlen(ptr2));
	close(fd);
	ft_alloc(0, ptr2, FREE_PTR);
	return (0);
}


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
		if (files->here_doc)
		{			
			if (change_content(files, env) == -1)
				return (-1);
		}
		if (helper_open_in_files(file_name, &last_fd) == -1)
			return (-1);
		if (files->next)
			close(last_fd);
		files = files->next;
	}
	return (last_fd);
}
