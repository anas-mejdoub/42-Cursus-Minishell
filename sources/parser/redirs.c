/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:51:18 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/29 16:55:16 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

bool	parser_redirs_switch(t_elem **elem, t_command **cmd, t_env *env)
{
	if (elem && (*elem)->type == REDIR_IN)
		(*cmd)->in_redir = true;
	else if (elem && (*elem)->type == REDIR_OUT)
		(*cmd)->out_redir = true;
	else if (elem && (*elem)->type == DREDIR_OUT)
		(*cmd)->dredir = true;
	else if (redir_out_condition(*elem, *cmd))
		redir_out_parse(elem, cmd, env);
	else if (elem && (*elem)->type == HERE_DOC)
		(*cmd)->here_doc = true;
	else if (redir_in_condition(*elem, *cmd))
		if (!redir_in_parse(elem, cmd, env))
			return (false);
	return (true);
}

bool	redir_in_parse(t_elem **elements, t_command **command, t_env *env)
{
	t_command_h_ret	*comm_hand_ret;
	t_elem			*tmp;
	t_bool_param	bool_param;

	tmp = NULL;
	comm_hand_ret = NULL;
	bool_param.bool1 = imbg(tmp, env);
	bool_param.bool1 = comm_hand_ret->wildcard;
	tmp = *elements;
	comm_hand_ret = command_handling(elements);
	if (handle_redir_in(*command, comm_hand_ret->command, bool_param, env) == \
	-1)
	{
		g_var = 1;
		return (false);
	}
	if ((*command)->in_redir)
	{
		(*command)->in_redir = false;
		add_indexs_to_infiles(comm_hand_ret->arr, comm_hand_ret->lens,
			get_last_in_file((*command)->in_files));
	}
	return (true);
}

void	redir_out_parse(t_elem **elements, t_command **command, t_env *env)
{
	t_command_h_ret	*comm_hand_ret;
	t_elem			*tmp;

	tmp = *elements;
	comm_hand_ret = command_handling(elements);
	handle_redir_out(*command, comm_hand_ret->command, imbg(tmp, env),
		comm_hand_ret->wildcard);
	add_indexs_to_outfiles(comm_hand_ret->arr, comm_hand_ret->lens,
		get_last_file((*command)->outfiles));
}

void	handle_redir_out(t_command *command, char *filename, bool ambiguous,
		bool wild_card)
{
	bool	append;

	command->out_redir = false;
	append = false;
	if (command->dredir)
		append = true;
	command->dredir = false;
	add_to_outfiles(command, new_file(filename, append, ambiguous, wild_card));
}

int	handle_redir_in(t_command *command, char *filename, t_bool_param bool_param,
		t_env *env)
{
	if (command->in_redir)
	{
		add_to_infiles(command, new_in_file(filename, false, bool_param.bool1,
				bool_param.bool2), env);
	}
	else if (command->here_doc)
	{
		command->here_doc = false;
		return (add_to_infiles(command, new_in_file(filename, true,
					bool_param.bool1, bool_param.bool2), env));
	}
	return (0);
}
