/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_back_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 22:41:03 by tisabel           #+#    #+#             */
/*   Updated: 2021/03/16 15:44:09 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*res;

	if (lst && new)
	{
		if (!(*lst))
			*lst = new;
		else
		{
			res = cmdlast(*lst);
			res->next = new;
			new->prev = res;
		}
	}
}
