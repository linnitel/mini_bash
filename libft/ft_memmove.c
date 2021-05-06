/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 21:16:21 by tisabel           #+#    #+#             */
/*   Updated: 2020/05/26 15:16:29 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*ptr_dst;
	unsigned char	*ptr_src;
	size_t			i;

	i = 0;
	if (!dst && !src)
		return (dst);
	ptr_src = (unsigned char*)src;
	ptr_dst = (unsigned char*)dst;
	if (ptr_src < ptr_dst)
		while (++i <= len)
			ptr_dst[len - i] = ptr_src[len - i];
	else
		while (i < len)
		{
			ptr_dst[i] = ptr_src[i];
			i++;
		}
	return (dst);
}
