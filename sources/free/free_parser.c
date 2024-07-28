/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:53:10 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/28 11:56:06 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_free.h"

void free_ret_parser(t_command_h_ret **ret)
{
    free((*ret)->command);
    (*ret)->command = NULL;
    free((*ret)->arr);
    (*ret)->arr = NULL;
    free((*ret)->lens);
    (*ret)->lens = NULL;
    free (*ret);
    *ret = NULL;
}