/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_case.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:44:49 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/29 15:05:52 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	handle_general_case(t_elem **element, t_command_h_ret *res)
{
	if (!res->command)
	{
		if ((*element)->type == WILDCARD)
			res->command = wild_card_handler(res);
		else
			res->command = ft_strdup((*element)->content);
	}
	else
	{
		if ((*element)->type != WHITE_SPACE)
		{
			if ((*element)->type == WILDCARD)
			{
				res->command = ft_freed_join(res->command,
						wild_card_handler(res));
			}
			else
				res->command = ft_freed_join(res->command, (*element)->content);
		}
	}
}

void	handle_env_case(t_elem **element, t_command_h_ret *res)
{
	res->arr = add_int(res->arr, env_index((*element)->content, res->command));
	res->lens = add_int(res->lens, (*element)->len);
	res->env = true;
}
