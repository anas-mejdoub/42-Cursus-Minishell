/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:07:06 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/27 14:37:33 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef AMBIGUOUS_H
# define AMBIGUOUS_H

# include "minishell.h"


char	*ambiguous(void *files, bool type, t_env *env);
bool    imbg(t_elem *tmp, t_env *env);
typedef struct s_amb_data
{
	int		**arr_env;
	char	**arr;
	int		size;
	int		index;
}			t_amb_data;

#endif