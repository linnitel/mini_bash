/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 10:30:27 by tisabel           #+#    #+#             */
/*   Updated: 2020/05/29 20:59:34 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr_b;

	i = 0;
	ptr_b = (unsigned char*)b;
	while (i < len)
	{
		ptr_b[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
