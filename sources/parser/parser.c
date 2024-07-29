/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:53:18 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/29 16:31:00 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

char	*wild_card_handler(t_command_h_ret *res)
{
	char	a[2];

	a[0] = -17;
	a[1] = '\0';
	res->wildcard = true;
	return (ft_strdup(a));
}

void	free2d(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		ft_alloc(0, str[i], FREE_PTR);
		i++;
	}
	ft_alloc(0, str, FREE_PTR);
}

t_command_h_ret	*intialize_ret_cmd(void)
{
	t_command_h_ret	*res;

	res = ft_alloc(sizeof(t_command_h_ret), NULL, MALLOC);
	if (!res)
		return (NULL);
	res->command = NULL;
	res->arr = NULL;
	res->wildcard = false;
	res->env = false;
	res->lens = NULL;
	res->including_null = false;
	return (res);
}

t_command	*parser(t_elem *elements, t_env *env)
{
	t_command	*command;
	t_command	*pipe_node;
	bool		ft;
	int			r;

	intialize_parser(&command, &pipe_node, &ft, &r);
	while (elements)
	{
		if (elements && elements->type == START_SUBSHELL
			&& !subshell_container(&elements, &command, env))
			return (NULL);
		else if (command_args_condition(elements, command))
			command_args_parse(&elements, &command);
		else if (split_tree_cond(elements, ft))
			split_tree(&elements, &command, &pipe_node, &r);
		else if (f_split_tree_cond(elements, ft))
			r = first_split_tree(elements, &command, &pipe_node, &ft);
		else if (!parser_redirs_switch(&elements, &command, env))
			return (NULL);
		if (elements)
			elements = elements->next;
		else
			break ;
	}
	return (pipe_node);
}
