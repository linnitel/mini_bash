/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:36:02 by tisabel           #+#    #+#             */
/*   Updated: 2021/03/16 15:44:09 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_arg(char *argum)
{
	int i;

	i = 0;
	while (argum[i] != '\0' && argum[i] != '=')
	{
		if (ft_isalpha(argum[i]) == 0)
		{
			if (argum[i] != '_' && ft_isdigit(argum[i]) == 0)
				return (1);
			if (ft_isdigit(argum[i]) == 1 && i == 0)
				return (1);
		}
		i++;
	}
	if (argum[i] == '=' && i == 0)
		return (1);
	return (0);
}

int			put_value(char *argum, t_env **temp)
{
	int n;

	free((*temp)->value);
	if ((n = ft_strfind(argum, '=')) != 0)
	{
		if (!((*temp)->value = ft_strdup(&argum[n])))
			return (2);
	}
	else if (!((*temp)->value = ft_strdup("")))
		return (2);
	return (0);
}
