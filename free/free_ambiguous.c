/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ambiguous.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:56:32 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/26 14:17:00 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_free.h"

// void free_ambg(t_amb_data **ambg)
// {

//     int i = 0;
//     while ((*ambg)->arr[i])
//     {
//         free((*ambg)->arr[i]);
//         i++;
//     }
//     free((*ambg)->arr);
//     i = 0;
//     while (i < (*ambg)->size)
//     {
//         free((*ambg)->arr_env[i]);
//         i++;
//     }
//     free((*ambg)->arr_env);
//     free((*ambg));
//     *ambg = NULL;
// }