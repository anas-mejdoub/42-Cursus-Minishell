/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 10:49:04 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/28 16:19:56 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_free.h"

static void	ft_elem_lstdelone(t_elem *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

void free_content(void *ptr)
{
	// free(ptr);
}

void	ft_elem_lstclear(t_elem **lst, void (*del)(void *))
{
	// t_elem	*temp;

	// if (!del || !lst || !(*lst))
	// 	return ;
	// temp = NULL;
	// while (*lst)
	// {
	// 	temp = *lst;
	// 	*lst = (*lst)->next;
	// 	ft_elem_lstdelone(temp, del);
	// }
	// *lst = NULL;
}
// void	free_elem(t_elem *elem)
// {
// 	t_elem	*prev;

// 	while (elem)
// 	{
// 		prev = elem;
// 		elem = elem->next;
// 		free(prev->content);
// 		free(prev);
// 	}
// }