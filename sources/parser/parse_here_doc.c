/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:43:26 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/29 15:14:26 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	handle_here_doc(t_in_files *file, t_env *env)
{
	char	*random;
	char	*file_name;
	int		i;
	char	*str1;

	(void)env;
	random = random_str();
	file_name = ft_strjoin("/tmp/", random);
	unlink(file_name);
	ft_alloc(0, random, FREE_PTR);
	ft_alloc(0, file->filename, FREE_PTR);
	file->filename = NULL;
	file->filename = ft_strdup(file_name);
	str1 = here_doc(file->limiter);
	if (str1 == NULL)
		return (ft_alloc(0, file_name, FREE_PTR), -1);
	i = open(file_name, O_CREAT | O_WRONLY | O_RDONLY, 0777);
	if (i == -1)
		return (ft_alloc(0, file_name, FREE_PTR),
			ft_putstr_fd("problem with opennig here doc\n", 2), -1);
	ft_putstr_fd(str1, i);
	close(i);
	ft_alloc(0, str1, FREE_PTR);
	ft_alloc(0, file_name, FREE_PTR);
	return (0);
}
