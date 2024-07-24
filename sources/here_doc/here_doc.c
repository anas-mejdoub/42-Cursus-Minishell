/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 10:17:55 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/24 16:10:22 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_here_doc.h"

static void save_heredoc_content(char *lim, int fd)
{
	char *content;
	char *line;
	char *tmp;

	content = malloc(1);
	content[0] = '\0';
	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			free(content);
			content = NULL;
			exit(0);
		}
		if (!ft_strncmp(line, lim, ft_strlen(lim)) && ft_strlen(lim) == ft_strlen(line))
			break ;
		tmp = ft_strjoin(content, ft_strjoin(line, "\n"));
		free(content);
		content = tmp;
	}
	write(fd, content, ft_strlen(content));
	close(fd);
	exit(0);
}


char	*here_doc(char *lim)
{
	int		status;
	pid_t	pid;

	signal (SIGINT, SIG_IGN);
	char *file =ft_strjoin("/tmp/" ,random_str());
	int fd = open(file, O_WRONLY | O_CREAT, 0777);
	if (fd < 0)
		return (NULL);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, kill_here_doc);
		save_heredoc_content(lim, fd);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		close(fd);
		if (WEXITSTATUS(status) == 1)	
			return (NULL);
		fd = open(file, O_RDONLY);
		if (fd < 0)
			return NULL;
			
		char *str = ft_calloc(1, 1);
		char buffer[1024];
		int bytesRead;
		while ((bytesRead = read(fd, buffer, sizeof(buffer)-1)) > 0)
		{
			buffer[bytesRead] = '\0';
			char *temp = ft_strjoin(str, buffer);
			free(str);
			str = temp;
		}
		close(fd);
		unlink(file);
		free(file);
		globalVar = 0;
		return (str);
	}
	return (NULL);
}
