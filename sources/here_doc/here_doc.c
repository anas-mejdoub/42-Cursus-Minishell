/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 10:17:55 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/06/24 14:49:49 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_here_doc.h"

char *expand_here_doc_content(char *str)
{
	t_list *list;
	int i;
	int s;

	i = 0;
	s = i;
	while (str[i])
	{
		while (str[i] != ENV)
			i++;
		if (str[i] == '$')
		{
			i++;
			ft_lstadd_back(&list, ft_lstnew(ft_substr(str, s, i - s)));
			s = i;
			while (ft_isalpha(str[i]) || str[i] == '_')
				i++;
			if (i != s + 1)
				ft_lstadd_back(&list, ft_lstnew(ft_substr(str, s, i - s)));
			if (str[i] == '*' || ft_isdigit(str[i]) || str[i] == '@')
			{
				memmove(str + i - 1, str +i + 1, strlen(str + i + 1) + 1);
				i--;
			}
		}
	}
	while (list)
	{
		printf("<%s>\n", list->content);
		list = list->next;
	}
	return (NULL);
}

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
