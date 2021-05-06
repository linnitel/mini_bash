/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 12:56:34 by tisabel           #+#    #+#             */
/*   Updated: 2020/08/16 01:57:02 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_count(char const *str, char c)
{
	unsigned int	i;
	unsigned int	nb;

	i = 0;
	nb = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i] != '\0')
		{
			nb++;
			while (str[i] != c && str[i] != '\0')
				i++;
		}
	}
	return (nb);
}

static void			ft_free_mem(char **res, unsigned int num)
{
	unsigned int	i;

	i = 0;
	while (i <= num)
	{
		free(res[i]);
		i++;
	}
	free(res);
}

static char			*ft_write_words(char const *s, char *word, char c,
									unsigned int i)
{
	unsigned int	j;
	unsigned int	nb;

	j = i;
	nb = 0;
	while (s[j] != c && s[j] != '\0')
	{
		nb++;
		j++;
	}
	word = (char*)malloc(sizeof(char) * (nb + 1));
	if (!word)
		return (NULL);
	j = 0;
	while (s[i] != c && s[i] != '\0')
	{
		word[j] = s[i];
		j++;
		i++;
	}
	word[j] = '\0';
	return (word);
}

char				**ft_split(char const *s, char c)
{
	unsigned int	i;
	unsigned int	j;
	char			**result;

	i = 0;
	j = 0;
	if (!s || !(result = (char**)malloc(sizeof(char*) * (ft_count(s, c) + 1))))
		return (NULL);
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			result[j] = ft_write_words(s, result[j], c, i);
			if (result[j] == NULL)
				ft_free_mem(result, j);
			while (s[i] != c && s[i] != '\0')
				i++;
			j++;
		}
	}
	result[j] = NULL;
	return (result);
}
