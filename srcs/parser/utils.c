/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 00:07:49 by mazor             #+#    #+#             */
/*   Updated: 2021/03/16 15:44:09 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** append character to string
**
** param **text pointer to string
** param c symbol
** return 0 if good, otherwise -1
*/

int		join_char(char **text, char c)
{
	char	*t;

	t = *text;
	if (!(*text = ft_strjoin_char(t, c)))
		return (-1);
	free(t);
	return (0);
}

/*
** join strings
**
** param **text pointer to string
** param *s string
** return 0 if good, otherwise -1
*/

int		join_str(char **text, char *s)
{
	if (!(*text = ft_strjoin(*text, s)))
		return (-1);
	return (0);
}

/*
** skip all spaces until a space is encountered
**
** param *all general structure
*/

void	trim_space(t_all *all)
{
	while (all->line[all->pos] && all->line[all->pos] == ' ')
		all->pos++;
}

/*
** re-malloc arguments and add 1 empty argument
**
** param **argv array of argument strings
** return pointer to an array of strings, otherwise NULL
*/

char	**remalloc_args(char **argv)
{
	int		i;
	char	**res;

	i = 0;
	while (argv[i])
		i++;
	if (!(res = ft_calloc(i + 2, sizeof(char*))))
		return (NULL);
	i = -1;
	while (argv[++i])
	{
		if (!(res[i] = ft_strdup(argv[i])))
			return (NULL);
		free(argv[i]);
		argv[i] = NULL;
	}
	free(argv);
	argv = NULL;
	if (!(res[i] = ft_strdup("")))
		return (NULL);
	res[i + 1] = 0;
	return (res);
}

/*
** re-malloc command arguments
**
** param *all general structure
** param *spec special characters
** param *i pointer to string index
** return 0 if good, otherwise -1
*/

int		add_remalloc_argv(t_all *all, t_cmd *lst, int *i)
{
	trim_space(all);
	if (!(lst->argv = remalloc_args(lst->argv)))
		return (-1);
	(*i)++;
	return (0);
}
