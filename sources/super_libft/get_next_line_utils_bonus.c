/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:28:33 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/01/10 16:12:12 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_gnl_bonus_strlen(char *ptr, char sep)
{
	size_t	i;

	i = 0;
	while (ptr && ptr[i] && ptr[i] != sep)
		i++;
	if (ptr && ptr[i] == '\n')
		i++;
	return (i);
}

char	*ft_gnl_bonus_strchr(const char *p, char ch)
{
	while (*p != '\0')
	{
		if (*p == (char)ch)
			return ((char *)p);
		p++;
	}
	return (NULL);
}

char	*ft_gnl_bonus_change_reminder(char *helper)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	ptr = (char *)malloc(BUFFER_SIZE + 1);
	if (!ptr)
		return (free(helper), NULL);
	i = 0;
	while (helper && helper[i] != '\n' && helper[i])
		i++;
	if (helper && helper[i] == '\n')
		i++;
	j = 0;
	while (helper && helper[i])
		ptr[j++] = helper[i++];
	while (j <= BUFFER_SIZE)
		ptr[j++] = '\0';
	return (free(helper), ptr);
}

char	*ft_gnl_bonus_join(char *ptr, char *helper)
{
	char	*newptr;
	int		i;
	int		ptrlen;

	if (!ptr && !helper)
		return (NULL);
	ptrlen = ft_gnl_bonus_strlen(ptr, '\0');
	newptr = (char *)malloc(ptrlen + ft_gnl_bonus_strlen(helper, '\n') + 1);
	if (!newptr)
		return (free(ptr), NULL);
	i = -1;
	while (ptr && ptr[++i])
		newptr[i] = ptr[i];
	i = 0;
	while (helper && helper[i] != '\n' && helper[i])
		newptr[ptrlen++] = helper[i++];
	if (helper && helper[i] && helper[i] == '\n')
		newptr[ptrlen++] = '\n';
	newptr[ptrlen] = '\0';
	return (free(ptr), newptr);
}

char	*ft_gnl_bonus_free(char **ptr1, char **ptr2)
{
	if (ptr1)
	{
		free(*ptr1);
		*ptr1 = NULL;
	}
	if (ptr2)
	{
		free(*ptr2);
		*ptr2 = NULL;
	}
	return (NULL);
}
