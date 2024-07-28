/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:11:02 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/28 16:59:03 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_here_doc.h"

static char	*concat_string(t_list *list)
{
	t_list	*tmp;
	char	*str;
	char	*tmp_str;

	tmp = list;
	// str = ft_calloc(1, 1);
	str = ft_alloc(1, NULL, CALLOC);
	while (tmp)
	{
		tmp_str = ft_strjoin(str, tmp->content);
		ft_alloc(0, str, FREE_PTR);
		// free(str);
		str = tmp_str;
		tmp = tmp->next;
	}
	return (str);
}

static t_list	*extract(char *str, int *i, int *start, t_env *env)
{
	char	*var;
	t_list	*lst;

	lst = NULL;
	if ((*i) != (*start))
	{
		var = env->get(env->data, ft_substr(str, (*start), (*i) - (*start)));
		if (var)
			lst = ft_lstnew(var);
		*start = *i;
		return (lst);
	}
	return (NULL);
}

static t_list	*create_list(char *str, t_env *env, int i, int start)
{
	t_list	*list;
	t_list	*newlist;

	list = NULL;
	while (str && str[i])
	{
		while (str && str[i] && str[i] != ENV)
			i++;
		if (start != i)
			ft_lstadd_back(&list, ft_lstnew(ft_substr(str, start, i - start)));
		if (str && str[i] && str[i] == ENV)
		{
			i++;
			start = i;
			if (str && str[i] && (ft_isalpha(str[i]) || str[i] == '_'))
			{
				while (str && str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
					i++;
				newlist = extract(str, &i, &start, env);
				if (newlist)
					ft_lstadd_back(&list, newlist);
			}
		}
	}
	return (list);
}

char	*expand_here_doc_content(char *str, t_env *env)
{
	int		i;
	int		start;
	t_list	*list;
	char	*string_final;

	i = 0;
	start = i;
	list = create_list(str, env, i, start);
	string_final = concat_string(list);
	ft_lstclear(&list, free_content);
	return (string_final);
}
