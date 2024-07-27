/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 11:15:20 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/26 14:17:05 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

#include "minishell.h"

void	ft_elem_lstclear(t_elem **lst, void (*del)(void *));
void free_content(void *ptr);
void free_ret_parser(t_command_h_ret **ret);
// void free_ambg(t_amb_data **ambg);

#endif