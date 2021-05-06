/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 13:00:31 by mazor             #+#    #+#             */
/*   Updated: 2021/03/16 15:44:09 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** gets command name from full path
**
** param *lst command pointer
** return pointer to the command name, otherwise NULL
*/

static char	*get_filename(t_cmd *lst)
{
	char	*res;

	if (!(res = ft_strrchr(lst->name, '/')))
		return (ft_strdup(lst->name));
	return (ft_strdup(++res));
}

/*
** clears strings
**
** param **split array of strings
** param **name pointer to string
** return NULL
*/

static void	*free_argv_local(char **split, char **name)
{
	free_array(split);
	if (name && *name)
		free(*name);
	return (NULL);
}

/*
** converts a list of environment variables to an array of strings
**
** param *all general structure
** return pointer to an array of strings, otherwise NULL
*/

char		**deconvert_env(t_env **my_env)
{
	t_env	*temp;
	char	**res;
	int		len;
	int		i;

	i = 0;
	temp = *my_env;
	len = count_env(temp);
	if (!(res = (char**)(malloc(sizeof(char*) * (len + 1)))))
		return (NULL);
	while (temp->next != NULL)
	{
		if (temp->standard != 0)
		{
			if (!(res[i] = ft_strdup(temp->name)) ||
				!(res[i] = ft_strjoin(res[i], "=")) ||
				!(res[i] = ft_strjoin(res[i], temp->value)))
				return (free_array(res));
		}
		i++;
		temp = temp->next;
	}
	res[i] = NULL;
	return (res);
}

/*
** converts command arguments to an array of strings
**
** param *lst argument list
** return pointer to an array of strings, otherwise NULL
*/

char		**convert_argv(t_cmd *lst)
{
	char	**res;
	char	*name;
	int		i;

	i = 0;
	while (lst->argv[i] &&
		ft_strncmp(lst->argv[i], "", 1))
		i++;
	if (!(res = ft_calloc(i + 2, sizeof(char*))))
		return (NULL);
	if (!(name = get_filename(lst)))
		return (free_array(res));
	if (!(res[0] = name))
		return (free_argv_local(res, &name));
	i = -1;
	while (lst->argv[++i])
	{
		if (ft_strncmp(lst->argv[i], "", 1))
		{
			if (!(res[i + 1] = ft_strdup(lst->argv[i])))
				return (free_argv_local(res, &name));
		}
	}
	return (res);
}
