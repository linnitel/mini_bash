/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_shielding.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazor <mazor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:08:15 by mazor             #+#    #+#             */
/*   Updated: 2021/03/16 15:44:09 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Produces shielding
**
** param *all general structure
** param **text pointer to the string to which the result is written
** return 0 if good, otherwise -1
*/

int		get_shielding(t_all *all, char **text)
{
	if (all->line[all->pos + 1])
	{
		if (join_char(text, all->line[all->pos + 1]) == -1)
			return (-1);
		all->pos += 2;
	}
	return (0);
}
