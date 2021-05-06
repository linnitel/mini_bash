/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 15:27:35 by tisabel           #+#    #+#             */
/*   Updated: 2020/05/29 21:01:26 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	letter;
	unsigned char	*ptr_s;
	size_t			i;

	i = 0;
	ptr_s = (unsigned char*)s;
	letter = (unsigned char)c;
	while (i < n)
	{
		if (ptr_s[i] == letter)
			return ((void*)ptr_s + i);
		i++;
	}
	return (NULL);
}
