/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:13:21 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/29 14:52:41 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

t_out_files	*new_file(char *filename, bool append, bool ambiguous,
		bool wild_card)
{
	t_out_files	*new;

	new = ft_alloc(sizeof(t_out_files), NULL, MALLOC);
	if (!new)
		return (NULL);
	new->filename = ft_strdup(filename);
	new->append = append;
	new->ambiguous = ambiguous;
	new->wildcard = wild_card;
	new->next = NULL;
	new->index_list = NULL;
	return (new);
}

t_out_files	*get_last_file(t_out_files *files)
{
	while (files && files->next)
	{
		files = files->next;
	}
	return (files);
}

void	add_to_outfiles(t_command *command, t_out_files *file)
{
	if (!command->outfiles)
		command->outfiles = file;
	else
		get_last_file(command->outfiles)->next = file;
}
