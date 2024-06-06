/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 10:40:50 by nbenyahy          #+#    #+#             */
/*   Updated: 2023/12/17 11:20:46 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*free2darr(char **arr, size_t a)
{
	size_t	i;

	i = 0;
	while (i < a && arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

static int	issep(char s, char c)
{
	if (s == c || s == '\0')
		return (1);
	return (0);
}

static size_t	wordcount(const char *s, char c)
{
	size_t	i;
	size_t	counter;

	i = 0;
	counter = 0;
	while (s[i])
	{
		if (!issep(s[i], c) && issep(s[i + 1], c))
			counter++;
		i++;
	}
	return (counter);
}

static char	**fillarr(char const *s, char c, char **arr)
{
	size_t	start;
	size_t	end;
	size_t	count;

	start = 0;
	end = 0;
	count = 0;
	while (s[start])
	{
		while (issep(s[start], c) && s[start])
			start++;
		if (!issep(s[start], c) && s[start])
		{
			end = 0;
			while (!issep(s[start + end], c) && s[start + end])
				end ++;
			arr[count] = ft_substr(s + start, 0, end);
			if (!arr[count])
				return (free2darr(arr, count));
			count ++;
			start += end;
		}
	}
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	size_t	count;
	char	**arr;

	if (!s)
		return (NULL);
	count = wordcount(s, c);
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	arr[count] = NULL;
	return (fillarr(s, c, arr));
}
