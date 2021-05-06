/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 23:02:59 by tisabel           #+#    #+#             */
/*   Updated: 2020/05/29 22:13:52 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*begin_new;

	if (!lst)
		return (NULL);
	new_lst = ft_lstnew(f(lst->content));
	if (!new_lst)
		return (NULL);
	begin_new = new_lst;
	while (lst)
	{
		if (lst->next != NULL)
		{
			new_lst->next = ft_lstnew(f(lst->next->content));
			if (new_lst->next == NULL)
			{
				ft_lstclear(&begin_new, del);
				return (NULL);
			}
			new_lst = new_lst->next;
		}
		lst = lst->next;
	}
	new_lst->next = NULL;
	return (begin_new);
}
