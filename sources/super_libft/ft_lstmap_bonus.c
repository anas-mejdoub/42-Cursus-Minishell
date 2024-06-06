/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:49:21 by nbenyahy          #+#    #+#             */
/*   Updated: 2023/12/17 16:37:05 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*freelst(t_list **newlst, void (*del)(void *), char *ptr)
{
	del(ptr);
	ft_lstclear(newlst, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newnode;
	t_list	*newlst;
	void	*ptr;

	newlst = NULL;
	newnode = NULL;
	ptr = NULL;
	while (lst && f && del)
	{
		ptr = f(lst->content);
		newnode = ft_lstnew(ptr);
		if (!newnode)
			return (freelst(&newlst, del, ptr));
		ft_lstadd_back(&newlst, newnode);
		lst = lst->next;
	}
	return (newlst);
}
