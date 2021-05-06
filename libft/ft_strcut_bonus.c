/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:18:45 by tisabel           #+#    #+#             */
/*   Updated: 2021/03/16 15:44:09 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The function cuts the string str by the character, cpecified in c.
** All that goes after c character is cutted. Returns a pointer to the
** beginning of the string that is left. If there is no c in str, returns str.
*/

char	*ft_strcut(char *str, char c)
{
	char	*new;
	int		len;
	int		i;

	if (!str)
		return (NULL);
	len = 0;
	i = 0;
	while (str[len] != c && str[len] != '\0')
		len++;
	if (!(new = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
