/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_ambiguous.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:05:44 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/26 10:06:17 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCAL_AMBIGUOUS_H
# define LOCAL_AMBIGUOUS_H

# include "ambiguous.h"
# include "minishell.h"

typedef struct s_amb_data
{
	int		**arr_env;
	char	**arr;
	int		size;
	int		index;
}			t_amb_data;

bool	sec_condition(t_amb_data *data, int j, char *ptr);

#endif