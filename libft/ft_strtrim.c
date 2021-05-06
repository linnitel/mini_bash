/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 19:51:41 by tisabel           #+#    #+#             */
/*   Updated: 2020/10/18 20:49:22 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_set_checker(const char c, char const *set)
{
	unsigned int	trueth;
	unsigned int	i;

	trueth = 0;
	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			trueth = 1;
		i++;
	}
	return (trueth);
}

static int		ft_trim_size_counter(char const *s1, char const *set, int end)
{
	int				i;
	unsigned int	len;

	len = 0;
	if (end == 1)
	{
		i = 0;
		while (s1[i] != '\0' && ft_set_checker(s1[i], set) == 1)
		{
			len++;
			i++;
		}
	}
	else
	{
		i = ft_strlen(s1) - 1;
		while (i >= 0 && ft_set_checker(s1[i], set) == 1)
		{
			len++;
			i--;
		}
	}
	return (len);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char			*trim_str;
	unsigned int	i;
	unsigned int	cut;
	unsigned int	len;

	i = 0;
	if (!set || !s1)
		return (NULL);
	cut = ft_trim_size_counter(s1, set, 1);
	if (cut == ft_strlen(s1))
		len = 0;
	else
		len = ft_strlen(s1) - (cut + ft_trim_size_counter(s1, set, 2));
	trim_str = (char*)malloc(sizeof(char) * (len + 1));
	if (!trim_str)
		return (NULL);
	while (i < len)
	{
		trim_str[i] = s1[i + cut];
		i++;
	}
	trim_str[i] = '\0';
	free((char*)s1);
	return (trim_str);
}
