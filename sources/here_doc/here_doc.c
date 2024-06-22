/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 10:17:55 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/06/22 18:55:20 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_here_doc.h"

char	*here_doc(char *lim)
{
	char	*line;
	char	*content = NULL;
	char	*tmp;
	int		a;
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		a = 1;
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
				exit(1);
			}
			if (ft_strnstr(line, lim, ft_strlen(line)))
				break ;
			tmp = ft_strjoin(content, ft_strjoin(line, "\n"));
			free(content);
			content = tmp;
		}
          return (content);
	}
	waitpid(pid, &status, 0);
     return (NULL);
}
