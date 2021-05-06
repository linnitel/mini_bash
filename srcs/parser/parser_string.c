/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 17:03:16 by mazor             #+#    #+#             */
/*   Updated: 2021/03/16 17:49:27 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** gets strings when encountering special characters
**
** param *all general structure
** param **text pointer to the string to which the result is written
** return 1 if a special character is encountered, 0 if not, -1 error
*/

int			get_spec(t_all *all, char **text)
{
	const char	spec[5] = "\\$\'\"";
	int			(*f[4])(t_all*, char**);
	int			i;

	i = -1;
	f[0] = get_shielding;
	f[1] = get_variables;
	f[2] = get_strong_quotes;
	f[3] = get_quotes;
	while (++i < (int)ft_strlen(spec))
	{
		if (all->line[all->pos] == spec[i])
		{
			if (f[i](all, text) == -1)
				return (-1);
			return (1);
		}
	}
	return (0);
}

/*
** gets the name of the command entered by the user
**
** param *all general structure
** return 0 if good, otherwise -1
*/

static int	get_name(t_all *all, t_cmd *lst)
{
	const char	spec[6] = " |;><";

	trim_space(all);
	while (all->line[all->pos] && !ft_strchr(spec, all->line[all->pos]))
	{
		if (!get_spec(all, &(lst->name)))
		{
			if (join_char(&(lst->name),
				all->line[all->pos]) == -1)
				return (-1);
			all->pos++;
		}
	}
	return (0);
}

/*
** gets all the arguments entered by the user
**
** param *all general structure
** return 0 if good, otherwise -1
*/

static int	get_arg(t_all *all, t_cmd *lst, int *i)
{
	const char	spec[6] = "|; ><";

	while (all->line[all->pos] && !ft_strchr(spec, all->line[all->pos]))
	{
		if (!get_spec(all, &lst->argv[*i]))
		{
			if (join_char(&lst->argv[*i], all->line[all->pos]) == -1)
				return (-1);
			all->pos++;
		}
	}
	if (*(lst->argv[*i]))
		if (add_remalloc_argv(all, lst, i) == -1)
			return (-1);
	return (0);
}

static int	get_tokens(t_all *all, t_cmd **lst)
{
	int			i;

	i = 0;
	if (all->line[all->pos] == ';')
		all->pos++;
	if (!(*lst = init_cmd()))
		return (-1);
	if (check_redir(all, *lst) == -1)
		return (-1);
	if (get_name(all, *lst) == -1)
		return (-1);
	while (all->line[all->pos] && !ft_strchr("|;", all->line[all->pos]))
	{
		if (check_redir(all, *lst) == -1)
			return (-1);
		if (get_arg(all, *lst, &i) == -1)
			return (-1);
	}
	return (0);
}

/*
** Parses the string entered by the user
**
** param *all general structure
** return 0 if good, otherwise -1
*/

int			parser_string(t_all *all)
{
	t_cmd		*lst;

	while (all->line[all->pos])
	{
		if (get_tokens(all, &lst))
			return (ft_error(NULL, "out of memory", 12, all));
		if (all->line[all->pos] == '|')
			lst->pipe = 1;
		if (!(*(lst->name)))
			clear_cmd(&lst);
		else
			cmdadd_back(&all->cmd, lst);
		if (all->line[all->pos] == ';')
		{
			all->semicol = 1;
			break ;
		}
		if (all->line[all->pos])
			all->pos++;
	}
	return (0);
}
