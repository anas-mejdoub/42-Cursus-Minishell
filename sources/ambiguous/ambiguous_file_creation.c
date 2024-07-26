/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_file_creation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:04:33 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/25 15:31:37 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_ambiguous.h"

static int	count_spaces(char *ptr)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	while (ptr[i])
	{
		if (ptr[i] == ' ')
			res++;
		i++;
	}
	return (res);
}

static char	*ambiguous_out_helper(t_env *env, t_out_files *file1)
{
	char	*file_name;

	file_name = NULL;
	if (file1->index_list || file1->wildcard)
		file_name = env_expander(file1->filename, file1->index_list, env,
				file1->wildcard);
	else
		file_name = file1->filename;
	if (file1->ambiguous || (ft_strchr(file_name, ' ')
			&& count_spaces(file_name) != count_spaces(file1->filename)
			&& file1->wildcard))
		return (print_err(2, 1, "minishell: : ambiguous redirect\n"), NULL);
	return (file_name);
}

static char	*ambiguous_in_helper(t_env *env, t_in_files *file2)
{
	char	*file_name;

	file_name = NULL;
	if (file2->index_list || file2->wildcard)
		file_name = env_expander(file2->filename, file2->index_list, env,
				file2->wildcard);
	else
		file_name = file2->filename;
	if (file2->ambiguous || (ft_strchr(file_name, ' ')
			&& count_spaces(file_name) != count_spaces(file2->filename)
			&& file2->wildcard))
		return (print_err(2, 1, "minishell: : ambiguous redirect\n"), NULL);
	return (file_name);
}

char	*ambiguous(void *files, bool type, t_env *env)
{
	t_out_files	*file1;
	t_in_files	*file2;

	file1 = NULL;
	file2 = NULL;
	if (type == true)
		return (ambiguous_out_helper(env, (t_out_files *)files));
	else
		return (ambiguous_in_helper(env, (t_in_files *)files));
}
