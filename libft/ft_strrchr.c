/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 15:14:49 by tisabel           #+#    #+#             */
/*   Updated: 2020/10/16 22:51:09 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	letter;
	int				i;

	i = 0;
	if (c < 0 || c > 255)
		return (NULL);
	letter = c;
	while (s[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (s[i] == letter)
			return ((char*)&s[i]);
		i--;
	}
	return (NULL);
}
