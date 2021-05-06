/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 15:24:53 by tisabel           #+#    #+#             */
/*   Updated: 2020/10/16 21:22:46 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 && s2 != NULL)
		return ((unsigned char)s2[i]);
	if (!s2 && s1 != NULL)
		return ((unsigned char)s1[i]);
	if (!s1 && !s2)
		return (0);
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && (i < n - 1) && (s1[i] != '\0' || s2[i] != '\0'))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
