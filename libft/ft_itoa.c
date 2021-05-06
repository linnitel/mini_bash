/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 17:09:36 by tisabel           #+#    #+#             */
/*   Updated: 2020/05/26 01:01:47 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_number_of_digits(long num)
{
	if (num < 0)
		return (1 + ft_number_of_digits(num * -1));
	if (num < 10)
		return (1);
	else
		return (1 + ft_number_of_digits(num / 10));
}

char		*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	number;
	int		i;

	number = n;
	len = ft_number_of_digits(number);
	i = len - 1;
	str = (char*)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	if (number < 0)
	{
		str[0] = '-';
		number = number * -1;
	}
	else if (number == 0)
		str[i] = '0';
	while (number > 0)
	{
		str[i--] = '0' + number % 10;
		number = number / 10;
	}
	str[len] = '\0';
	return (str);
}
