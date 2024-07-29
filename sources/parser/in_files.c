/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:54:17 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/29 15:06:05 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

t_in_files	*new_in_file(char *filename, bool here_doc, bool env_qoute,
		bool wild_card)
{
	t_in_files	*new;

	new = ft_alloc(sizeof(t_in_files), NULL, MALLOC);
	if (!new)
		return (NULL);
	new->filename = ft_strdup(filename);
	new->here_doc = here_doc;
	new->ambiguous = env_qoute;
	new->limiter = NULL;
	new->wildcard = wild_card;
	new->index_list = NULL;
	new->next = NULL;
	if (here_doc)
	{
		new->limiter = ft_strdup(filename);
	}
	return (new);
}

t_in_files	*get_last_in_file(t_in_files *files)
{
	while (files && files->next)
	{
		files = files->next;
	}
	return (files);
}

int	add_to_infiles(t_command *command, t_in_files *file, t_env *env)
{
	if (!command->in_files)
	{
		command->in_files = file;
	}
	else
		get_last_in_file(command->in_files)->next = file;
	if (file->here_doc)
	{
		if (handle_here_doc(file, env) == -1)
			return (-1);
	}
	return (0);
}
