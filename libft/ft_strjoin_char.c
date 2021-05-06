/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazor <mazor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:19:58 by mazor             #+#    #+#             */
/*   Updated: 2021/03/16 15:44:09 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_char(char const *s1, char c)
{
	char	*res;
	int		i;

	if (!c)
		return (NULL);
	if (s1)
	{
		i = ft_strlen((char*)s1) + 2;
		if (!(res = malloc(sizeof(char) * i)))
			return (NULL);
		ft_strlcpy(res, (char *)s1, ft_strlen((char *)s1) + 1);
	}
	else
	{
		i = 2;
		if (!(res = malloc(sizeof(char) * i)))
			return (NULL);
	}
	res[i - 2] = c;
	res[i - 1] = '\0';
	return (res);
}
