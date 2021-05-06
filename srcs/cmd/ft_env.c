/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:48:51 by mazor             #+#    #+#             */
/*   Updated: 2021/03/16 15:44:09 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** executes the env command
**
** param *all general structure
** param *cmd command structure
** return 0
*/

int		ft_env(t_all *all, t_cmd *cmd)
{
	t_env *temp;

	temp = all->my_env;
	all->exit_status = 0;
	if (ft_strcmp(cmd->argv[0], "") != 0)
	{
		ft_error("env", "Wrong number of arguments", 21, all);
		return (all->exit_status);
	}
	else
		while (temp != NULL)
		{
			if (*(temp->value) != '\0')
			{
				write(1, temp->name, ft_strlen(temp->name));
				write(1, "=", 1);
				write(1, temp->value, ft_strlen(temp->value));
				write(1, "\n", 1);
			}
			temp = temp->next;
		}
	return (all->exit_status);
}
