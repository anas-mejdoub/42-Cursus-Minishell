/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:00:13 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/29 14:51:28 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

t_command_h_ret	*command_handling(t_elem **element)
{
	t_command_h_ret	*res;
	t_elem			*tmp;

	res = intialize_ret_cmd();
	tmp = NULL;
	if ((*element)->type == ENV)
		res->env = true;
	while (*element)
	{
		if (ft_strchr(" ><|()&", (*element)->type)
			&& (*element)->state == GENERAL && (*element)->type != QOUTE)
		{
			*element = tmp;
			return (res);
		}
		command_handl_core(element, res);
		tmp = *element;
		*element = (*element)->next;
	}
	if (!res->command)
		res->command = ft_strdup("");
	return (res);
}

void	command_handl_core(t_elem **element, t_command_h_ret *res)
{
	if (((*element)->type == QOUTE && (*element)->next
			&& ((t_elem *)(*element)->next)->type == QOUTE)
		|| ((*element)->type == DOUBLE_QUOTE && (*element)->next
			&& ((t_elem *)(*element)->next)->type == DOUBLE_QUOTE))
		handle_empty_quote(res);
	if ((*element)->type == DOUBLE_QUOTE || (*element)->type == QOUTE)
		res->including_null = true;
	if ((*element)->type == ENV)
		handle_env_case(element, res);
	if (((*element)->state == IN_QUOTE || (*element)->state == IN_DQUOTE)
		&& ((*element)->type != DOUBLE_QUOTE && (*element)->type != QOUTE))
		handle_quotes_case(element, res);
	else if ((*element)->state == GENERAL && (*element)->type != QOUTE
		&& (*element)->type != DOUBLE_QUOTE)
		handle_general_case(element, res);
}

void	handle_quotes_case(t_elem **element, t_command_h_ret *res)
{
	if (!res->command)
		res->command = ft_strdup((*element)->content);
	else
		res->command = ft_freed_join(res->command, (*element)->content);
}

void	handle_empty_quote(t_command_h_ret *res)
{
	if (!res->command)
		res->command = ft_strdup("");
}
