/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 19:16:24 by tisabel           #+#    #+#             */
/*   Updated: 2020/05/29 21:21:07 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*temp;
	int		len;

	temp = lst;
	len = 0;
	if (lst != NULL)
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
			len++;
		}
		len++;
	}
	return (len);
}
