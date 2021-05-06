/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 19:25:55 by tisabel           #+#    #+#             */
/*   Updated: 2020/07/27 05:09:49 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joint_str;
	size_t	i;
	size_t	j;
	size_t	len_s1;
	size_t	len_s2;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	joint_str = (char*)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!joint_str)
		return (0);
	while (i < len_s1)
	{
		joint_str[i] = s1[i];
		i++;
	}
	free((char*)s1);
	while (i < len_s1 + len_s2)
		joint_str[i++] = s2[j++];
	joint_str[i] = '\0';
	return (joint_str);
}
