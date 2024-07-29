/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_creation_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:22:07 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/29 11:30:02 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_helper.h"

static char	*read_file(int fd)
{
	char	buffer[1024];
	char	*ptr;
	int		readbyte;

	readbyte = 0;
	ptr = ft_alloc(1, NULL, CALLOC);
	while (1)
	{
		readbyte = read(fd, buffer, 1024);
		if (readbyte < 0)
			return (print_err(2, 1, "error while reading heredoc file"), NULL);
		if (readbyte == 0)
			break ;
		buffer[readbyte] = '\0';
		ptr = ft_freed_join(ptr, buffer);
	}
	close(fd);
	return (ptr);
}

int	change_content(t_in_files *file, t_env *env)
{
	char	*ptr;
	char	*ptr2;
	int		fd;

	fd = open(file->filename, O_RDONLY);
	if (fd < 1)
		return (print_err(2, 1, "error while opening heredoc file"), -1);
	ptr = read_file(fd);
	if (ptr == NULL)
		return (-1);
	ptr2 = expand_here_doc_content(ptr, env);
	ft_alloc(0, ptr, FREE_PTR);
	fd = open(file->filename, O_WRONLY | O_TRUNC);
	if (fd < 0)
		return (print_err(2, 1, "error while writing in heredoc file"), -1);
	write(fd, ptr2, ft_strlen(ptr2));
	close(fd);
	ft_alloc(0, ptr2, FREE_PTR);
	return (0);
}
