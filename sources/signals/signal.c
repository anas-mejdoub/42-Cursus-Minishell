/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 07:31:40 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/29 11:50:48 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_signal.h"

void	new_prompt(int sig)
{
	(void)sig;
	g_var = 1;
	printf(BHMAG "\n" RESET);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	kill_here_doc(int sig)
{
	(void)sig;
	printf("\n");
	exit(1);
}
