/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:36:05 by nbenyahy          #+#    #+#             */
/*   Updated: 2023/12/27 12:39:49 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	helper_fun(char a, va_list args, int *res)
{
	if (a == 'c')
		ft_putchar(va_arg(args, int), res);
	else if (a == 's')
		ft_putstr(va_arg(args, char *), res);
	else if (a == 'd' || a == 'i')
		ft_putnbr(va_arg(args, int), res);
	else if (a == 'u')
		ft_putnbr(va_arg(args, unsigned int), res);
	else if (a == 'x' || a == 'X')
		ft_puthexa(va_arg(args, unsigned int), a, res);
	else if (a == 'p')
		ft_puthexa(va_arg(args, unsigned long), a, res);
	else
		ft_putchar(a, res);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		res;

	i = 0;
	res = 0;
	if (write(1, "", 0) == -1)
		return (-1);
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			i++;
			if (format[i] == '%')
				ft_putchar('%', &res);
			else
				helper_fun(format[i], args, &res);
		}
		else if (format[i] != '%')
			ft_putchar(format[i], &res);
		i++;
	}
	va_end(args);
	return (res);
}
