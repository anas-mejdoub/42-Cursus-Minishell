/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 17:06:12 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/29 11:13:25 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_env.h"

static size_t	nbrlen(int n)
{
	size_t	size;

	size = 0;
	if (n < 0)
		size++;
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_strdap(const char *s)
{
	char	*ptr;
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	ptr = (char *)malloc((sizeof(char) * (len + 1)));
	if (!ptr)
	{
		return (NULL);
	}
	i = 0;
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_itua(int n)
{
	size_t	size;
	char	*res;

	if (n == 0)
		return (ft_strdap("0"));
	else if (n == -2147483648)
		return (ft_strdap("-2147483648"));
	size = nbrlen(n);
	res = (char *)malloc(((size + 1) * sizeof(char)));
	if (!res)
		return (NULL);
	if (n < 0)
	{
		n = -n;
		res[0] = '-';
	}
	res[size] = '\0';
	while (n)
	{
		size--;
		res[size] = n % 10 + 48;
		n /= 10;
	}
	return (res);
}

char	*ft_sabstr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	orgstart;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	orgstart = start;
	while (start < len + orgstart && s[start])
	{
		ptr[i] = s[start];
		i++;
		start++;
	}
	ptr[i] = '\0';
	return (ptr);
}
