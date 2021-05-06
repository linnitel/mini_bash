/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 16:46:35 by tisabel           #+#    #+#             */
/*   Updated: 2020/07/27 05:10:35 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Allocates memory and copies the string
** to the new place.
*/

char	*ft_strdup(const char *s1)
{
	unsigned int	length;
	unsigned int	i;
	char			*copy;

	i = 0;
	length = 0;
	while (s1[length] != '\0')
		length++;
	copy = (char *)malloc(length + 1);
	if (!copy)
		return (NULL);
	while (i < length)
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
