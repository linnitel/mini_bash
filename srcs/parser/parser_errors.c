/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 11:57:19 by mazor             #+#    #+#             */
/*   Updated: 2021/03/16 15:44:09 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** displays an error
**
** param *all general structure
** param *text error text
** return 1
*/

int			ret_err(t_all *all, char *text)
{
	all->res = 2;
	return (ft_error(NULL, text, 258, all));
}

/*
** Handles syntax errors
**
** param *all general structure
** param *lst command pointer
** return 0 if no error was found, 1 error was found
*/
