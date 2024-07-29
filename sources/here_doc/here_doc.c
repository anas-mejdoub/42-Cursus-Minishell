/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 10:17:55 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/29 09:18:08 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_here_doc.h"

static void save_heredoc_content(char *lim, char *file)
{
	char	*content;
	char	*line;
	int		fd;

	content = ft_alloc(1, NULL, CALLOC);
	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			ft_alloc(0, content, FREE_PTR);
			exit(0);
		}
		if (!ft_strncmp(line, lim, ft_strlen(lim))
			&& ft_strlen(lim) == ft_strlen(line))
			{
			free(line);
			break ;
			}
		content = ft_freed_join(content, line);
		content = ft_freed_join(content, "\n");	
		free(line);
	}
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
	{
		ft_alloc(0, file, FREE_PTR);
		exit(1);
	}
	write(fd, content, ft_strlen(content));
	close(fd);
	ft_alloc(0, content, FREE_PTR);
	exit(0);
}

static char	*read_heredoc_content(char *file)
{
	int		fd;
	char	*str;
	char	buffer[1024];
	int		bytes_read;
	char	*temp;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	str = ft_alloc(1, NULL, CALLOC);
	while (1)
	{
		bytes_read = read(fd, buffer, sizeof(buffer) - 1);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(str, buffer);
		ft_alloc(0, str, FREE_PTR);
		str = temp;
	}
	close(fd);
	unlink(file);
	ft_alloc(0, file, FREE_PTR);
	g_var = 0;
	return (str);
}

char	*here_doc(char *lim)
{
	int		status;
	char 	*rand;
	pid_t	pid;
	char	*file;

	signal(SIGINT, SIG_IGN);
	rand = random_str();
	file = ft_strjoin("/tmp/", rand);
	ft_alloc(0, rand, FREE_PTR);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, kill_here_doc);
		save_heredoc_content(lim, file);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WEXITSTATUS(status) == 1)
			return (ft_alloc(0, file, FREE_PTR), NULL);
		return (read_heredoc_content(file));
	}
	return (ft_alloc(0, file, FREE_PTR), NULL);
}
