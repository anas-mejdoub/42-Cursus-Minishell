/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 10:56:36 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/29 11:01:10 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	v_close_fd(int n, ...)
{
	va_list	l;
	int		i;
	int		fd;

	i = 0;
	fd = -1;
	va_start(l, n);
	while (i < n)
	{
		fd = va_arg(l, int);
		if (fd == -1)
			break ;
		close(fd);
		i++;
	}
	va_end(l);
}

void	print_err_exit(int count, ...)
{
	int		i;
	char	*str;
	va_list	args;

	i = 0;
	va_start(args, count);
	g_var = va_arg(args, int);
	i++;
	ft_putstr_fd(RED, 2);
	while (i < count)
	{
		str = va_arg(args, char *);
		ft_putstr_fd(str, 2);
		i++;
	}
	ft_putstr_fd(RESET, 2);
	va_end(args);
	exit(g_var);
}

void	close_fds(int *arr)
{
	int	i;

	i = 0;
	while (arr)
	{
		if (arr[i] == -1)
			break ;
		close(arr[i]);
		i++;
	}
}

void	share_fds(t_command *command)
{
	if (command->outfd != -1)
	{
		((t_command *)command->right)->outfd = command->outfd;
		((t_command *)command->left)->outfd = dup(command->outfd);
	}
	if (command->infd != -1)
	{
		((t_command *)command->right)->infd = command->infd;
		((t_command *)command->left)->infd = dup(command->infd);
	}
	((t_command *)command->left)->fd[0] = command->fd[0];
	((t_command *)command->left)->fd[1] = command->fd[1];
	((t_command *)command->right)->fd[0] = command->fd[0];
	((t_command *)command->right)->fd[1] = command->fd[1];
}
