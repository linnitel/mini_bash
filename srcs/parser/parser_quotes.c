/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazor <mazor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 18:31:34 by mazor             #+#    #+#             */
/*   Updated: 2021/03/16 15:44:09 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** gets a string inside strong quotes
**
** param *all general structure
** param **text pointer to the string to which the result is written
** return 0 if good, otherwise -1
*/

int		get_strong_quotes(t_all *all, char **text)
{
	all->pos++;
	while (all->line[all->pos] && all->line[all->pos] != '\'')
	{
		if (join_char(text, all->line[all->pos]) == -1)
			return (-1);
		all->pos++;
	}
	if (all->line[all->pos] == '\'')
		all->pos++;
	return (0);
}

/*
** gets the string inside the loose quotes
**
** param *all general structure
** param **text pointer to the string to which the result is written
** return 0 if good, otherwise -1
*/

int		get_quotes(t_all *all, char **text)
{
	all->pos++;
	while (all->line[all->pos] && all->line[all->pos] != '\"')
	{
		if (all->line[all->pos] == '\\' &&
		ft_strchr("$\"\\", all->line[all->pos + 1]))
		{
			if (get_shielding(all, text) == -1)
				return (-1);
		}
		else if (all->line[all->pos] == '$' && all->line[all->pos - 1] != '\\')
		{
			if (get_variables(all, text) == -1)
				return (-1);
		}
		else
		{
			if (join_char(text, all->line[all->pos]) == -1)
				return (-1);
			all->pos++;
		}
	}
	if (all->line[all->pos] == '\"')
		all->pos++;
	return (0);
}
