/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 15:20:30 by tisabel           #+#    #+#             */
/*   Updated: 2020/05/29 20:59:37 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*string1_ptr;
	unsigned char	*string2_ptr;

	if (n == 0 || s1 == s2)
		return (0);
	i = 0;
	string1_ptr = (unsigned char*)s1;
	string2_ptr = (unsigned char*)s2;
	while (i < n)
	{
		if (string1_ptr[i] != string2_ptr[i])
			return (string1_ptr[i] - string2_ptr[i]);
		i++;
	}
	return (0);
}
