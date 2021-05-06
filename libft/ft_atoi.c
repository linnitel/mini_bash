/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 12:35:56 by tisabel           #+#    #+#             */
/*   Updated: 2021/03/17 10:03:54 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Converts a string into an int.
*/

static int	ft_cut(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r')
		i++;
	return (i);
}

static int	ft_check_sighn(const char *str)
{
	int				sighn;
	unsigned int	i;

	sighn = 1;
	i = ft_cut(str);
	if (str[i] == '-')
		sighn = -1;
	return (sighn);
}

int			ft_atoi(const char *str)
{
	int					i;
	unsigned long long	num;
	int					sighn;

	i = ft_cut(str);
	num = 0;
	sighn = ft_check_sighn(str);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		if (num == 922337203685477580 && str[i] == '8')
			return ((num * 10 + (str[i + 1] - '0')) * sighn);
		i++;
	}
	if (num > 9223372036854775807 && sighn == 1)
		return (-1);
	if (num > 9223372036854775807 && sighn == -1)
		return (0);
	return (num * sighn);
}
