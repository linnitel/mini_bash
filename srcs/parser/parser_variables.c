/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 00:04:57 by mazor             #+#    #+#             */
/*   Updated: 2021/03/17 10:16:32 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** display the result of the last operation
**
** param *all general structure
** param **text pointer to the string to which the result is written
** return 1 if there was $?, If not 0, error -1
*/

static int	get_result(t_all *all, char **text)
{
	char	*num;

	if (all->line[all->pos] == '?')
	{
		if (!(num = ft_itoa(all->exit_status)))
			return (-1);
		if (join_str(text, num) == -1)
			return (-1);
		free(num);
		all->pos++;
		return (1);
	}
	return (0);
}

/*
** Replaces text with the value of an environment variable
**
** param *all general structure
** param **text pointer to the string to which the result is written
** param *var environment variable name
** return 0 if good, otherwise -1
*/

static int	set_env(t_all *all, char **text, char *var)
{
	char *temp;

	temp = get_var(all->my_env, var);
	if (!temp)
		return (-1);
	if (join_str(text, temp) == -1)
	{
		free(temp);
		return (-1);
	}
	free(temp);
	return (0);
}

static int	free_var(char **var)
{
	free(*var);
	return (0);
}

/*
** Replaces text with the value of an environment variable
**
** param *all general structure
** param **text pointer to the string to which the result is written
** return 0 if good, otherwise -1
*/

int			get_variables(t_all *all, char **text)
{
	char		*var;
	const char	spec[10] = " \'\";|><$?=";
	int			res;

	all->pos++;
	var = NULL;
	if ((res = get_result(all, text)) == -1)
		return (-1);
	if (!res)
	{
		if (ft_isalnum(all->line[all->pos]) == 1)
		{
			while (all->line[all->pos] && !ft_strchr(spec, all->line[all->pos]))
			{
				if (join_char(&var, all->line[all->pos]) == -1)
					return (-1);
				all->pos++;
			}
			if (set_env(all, text, var) == -1)
				return (-1);
		}
		else
			return (join_char(text, '$'));
	}
	return (free_var(&var));
}
