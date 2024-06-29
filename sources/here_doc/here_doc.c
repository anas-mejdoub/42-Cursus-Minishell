/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 10:17:55 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/06/29 11:07:57 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_here_doc.h"

char *concat_string(t_list *list)
{
	t_list *tmp;
	
	tmp = list;
	char *str;
	char *tmp_str;

	str = ft_calloc(1, 1);
	while (tmp)
	{
		tmp_str = ft_strjoin(str, tmp->content);
		free(str);
		str = tmp_str;
		tmp = tmp->next;
	}
	return (str);
}

void free_list(void *ptr)
{
	free(ptr);
}

char	*expand_here_doc_content(char *str, t_env *env)
{
	t_list	*list;
	char *var;
	int		i;
	int		s;
	char *string_final;

	i = 0;
	s = i;
	list = NULL;
	while (str && str[i])
	{
		while (str && str[i] && str[i] != ENV)
			i++;
		if (s != i)
			ft_lstadd_back(&list, ft_lstnew(ft_substr(str, s, i - s)));
		if (str && str[i] && str[i] == ENV)
		{
			i++;
			s = i;
			if (str && str[i] && (ft_isalpha(str[i]) || str[i] == '_'))
			{
				while (str && str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
					i++;
				if (i != s)
				{
					var = env->get(env->data, ft_substr(str, s, i - s + 1));
					if (var)
						ft_lstadd_back(&list, ft_lstnew(var));
					s = i;
				}
			}
		}
	}
	string_final = concat_string(list);
	ft_lstclear(&list, free_list);
	return (string_final);
}
void kill_here_doc(int sig)
{
	(void)sig;
	exit(0);
}

char	*here_doc(char *lim)
{
	char	*line;
	char	*content;
	char	*tmp;
	int		a;
	int		status;
	pid_t	pid;

	content = NULL;
	signal (SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, kill_here_doc);
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
			if (!ft_strncmp(line, lim, ft_strlen(lim)) && ft_strlen(lim) == ft_strlen(line))
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
