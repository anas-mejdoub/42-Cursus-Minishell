/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 10:47:54 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/06/30 17:59:06 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
#define HERE_DOC_H

# include "minishell.h"

char    *here_doc(char *lim);
char *expand_here_doc_content(char *str, t_env *env);

#endif
