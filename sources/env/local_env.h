/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_env.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 10:30:33 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/28 17:13:37 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCAL_ENV_H
# define LOCAL_ENV_H

# include "env.h"
# include "minishell.h"

char	*ft_strdap(const char *s);
char	*ft_itua(int n);
char	*ft_sabstr(char const *s, unsigned int start, size_t len);

void	init_env_methods(t_env **env);


#endif