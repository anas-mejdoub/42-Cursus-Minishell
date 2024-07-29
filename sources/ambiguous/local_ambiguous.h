/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_ambiguous.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:05:44 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/29 11:12:25 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCAL_AMBIGUOUS_H
# define LOCAL_AMBIGUOUS_H

# include "ambiguous.h"
# include "minishell.h"

bool	sec_condition(t_amb_data *data, int j, char *ptr);
void	fill_array_element(t_amb_data *data, t_elem *tmp, t_env *env);

#endif