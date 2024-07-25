/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 12:35:45 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/25 15:01:56 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_helper.h"

char	*add_string_back(char **s1, char **s2)
{
	char	*tmp;

	if ((*s2) == NULL)
		return ((*s1));
	tmp = ft_strjoin(*s1, *s2);
	*s1 = tmp;
	return (*s1);
}

static void	add_vars(char *tmp_str, t_env *env, char **str, char **s)
{
	*s = env->get(env->data, tmp_str);
	if (*s && ft_strchr(*s, '*'))
		*s = wildcard_expander(*s);
	add_string_back(str, s);
}

static void	add_vars2(char *tmp_str, int *i, int *start, char **str)
{
	*str = add_string_back(str, &tmp_str);
	*start = *i;
}

static char	*expand_content(char *content, t_env_index *tmp_index, t_env *env)
{
	int		i;
	int		start;
	char	*str;
	char	*s;

	i = 0;
	start = i;
	str = ft_calloc(1, 1);
	while (content[i])
	{
		while ((!tmp_index && content[i]) || (content[i] && tmp_index
				&& i != tmp_index->index))
			i++;
		if (i != start)
			add_vars2(ft_substr(content, start, i - start), &i, &start, &str);
		if (tmp_index && i == tmp_index->index)
		{
			add_vars(ft_substr(content, start + 1, tmp_index->len - 1), env,
				&str, &s);
			start = ++i + tmp_index->len - 1;
			tmp_index = tmp_index->next;
		}
	}
	return (str);
}

char	*env_expander(char *content, t_env_index *indexs, t_env *env,
		bool wild_card)
{
	t_env_index	*tmp_index;
	char		*new_content;

	(void)env;
	tmp_index = indexs;
	if (wild_card)
	{
		new_content = wildcard(content, -17);
		content = new_content;
	}
	if (!indexs)
		return (content);
	return (expand_content(content, tmp_index, env));
}
