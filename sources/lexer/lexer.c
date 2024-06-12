/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:12:28 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/06/12 15:59:39 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void tokenize(char *line)
{
    
}


void lexer()
{
    while (1)
    {
        char* line = readline("tchbi7a-shell$");
        if (line) {
            tokenize(line);
            free(line);
        }
    }
}

int main() {
    lexer();
    return 0;
}