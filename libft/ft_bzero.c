/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 15:19:12 by tisabel           #+#    #+#             */
/*   Updated: 2020/05/22 08:56:49 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;
	unsigned char	*ptr_s;

	ptr_s = (unsigned char*)s;
	i = 0;
	if (n == 0)
		return ;
	while (i < n)
	{
		ptr_s[i] = '\0';
		i++;
	}
}
