/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:27:44 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/25 12:12:43 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_helper.h"
#include <stdarg.h>

void	print_err(int count, ...)
{
	int		i;
	char	*str;
	va_list	args;

	i = 0;
	va_start(args, count);
	globalVar = va_arg(args, int);
	i++;
	ft_putstr_fd(RED, 2);
	while (i < count)
	{
		// printf ("%d\n", i);
		str = va_arg(args, char *);
		ft_putstr_fd(str, 2);
		i++;
	}
	ft_putstr_fd(RESET, 2);
	va_end(args);
}
