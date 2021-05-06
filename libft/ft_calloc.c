/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 15:29:17 by tisabel           #+#    #+#             */
/*   Updated: 2020/05/26 15:46:41 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*new;

	i = 0;
	new = malloc((size * count));
	if (new == NULL)
		return (NULL);
	while (i < count * size)
	{
		new[i] = '\0';
		i++;
	}
	return (new);
}
