/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:16:54 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/25 09:40:22 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_wildcard.h"

static char	**dir_content(void)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**arr;
	char			cwd[1024];

	arr = NULL;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (perror("getcwd"), NULL);
	dir = opendir(cwd);
	if (dir == NULL)
		return (perror("opendir"), NULL);
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (entry->d_name[0] != '.')
			arr = add_to_args(arr, entry->d_name);
	}
	closedir(dir);
	return (arr);
}

static bool	matching_pattern(char *s1, char *s2, char reg)
{
	if (*s2 == '\0')
		return (*s1 == '\0');
	if (*s2 == reg)
		return (matching_pattern(s1, s2 + 1, reg) || (*s1 && matching_pattern(s1
					+ 1, s2, reg)));
	if (*s1 == *s2)
		return (matching_pattern(s1 + 1, s2 + 1, reg));
	return (false);
}

static char	*original_string(char *pattern)
{
	char	*new_ptr;
	int		j;

	j = 0;
	if (!pattern)
		return (NULL);
	new_ptr = malloc(ft_strlen(pattern) + 1);
	while (pattern[j])
	{
		if (pattern[j] == -17)
			new_ptr[j] = '*';
		else
			new_ptr[j] = pattern[j];
		j++;
	}
	new_ptr[j] = '\0';
	return (new_ptr);
}

static char	*join_arr(char **arr)
{
	int		i;
	char	*final_content;

	i = 0;
	if (!arr)
		return (NULL);
	final_content = ft_calloc(1, 1);
	while (arr[i])
	{
		final_content = ft_strjoin(final_content, arr[i]);
		i++;
		if (arr[i])
			final_content = ft_strjoin(final_content, " ");
	}
	return (final_content);
}

char	*wildcard(char *pattern, char reg)
{
	char	**content;
	char	**arr_final;
	int		i;

	arr_final = NULL;
	content = dir_content();
	i = 0;
	while (content[i])
	{
		if (matching_pattern(content[i], pattern, reg) == true)
			arr_final = add_to_args(arr_final, content[i]);
		i++;
	}
	if (arr_final == NULL)
		return (original_string(pattern));
	else
		return (join_arr(arr_final));
	return (NULL);
}
