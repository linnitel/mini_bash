/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 18:00:54 by mazor             #+#    #+#             */
/*   Updated: 2021/03/16 17:16:44 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** looks for a file in a directory
**
** param *path path to directory
** param *name file name
** return 1 if the file is found, otherwise 0
*/

static int	get_cd_local(char *path, char *name)
{
	DIR				*dir;
	struct dirent	*item;

	if (!(dir = opendir(path)))
		return (0);
	while ((item = readdir(dir)))
	{
		if (!ft_strncmp(item->d_name, name, ft_strlen(name) + 1))
		{
			closedir(dir);
			return (1);
		}
	}
	closedir(dir);
	return (0);
}

/*
** get full command path
**
** param **split an array of path strings for the PATH variable
** param *all general structure
** param *lst command pointer
** return full file path, otherwise NULL
*/

static char	*parse_split_local(char **split, t_all *all, t_cmd *lst)
{
	int		i;
	char	*res;

	i = -1;
	res = NULL;
	while (split[++i])
	{
		if (get_cd_local(split[i], lst->name) == 1)
		{
			if (!(res = ft_strjoin_char(split[i], '/')) ||
				join_str(&res, lst->name) == -1)
			{
				if (res)
					free(res);
				return (NULL);
			}
			return (res);
		}
	}
	ft_error(lst->name, "command not found", 127, all);
	all->res = 127;
	return (NULL);
}

/*
** get full command path
**
** param *all general structure
** param *lst command pointer
** return full file path, otherwise NULL
*/

char		*get_full_cmd_name(t_all *all, t_cmd *lst)
{
	char	**split;
	char	*env;
	char	*res;

	if (ft_strchr(lst->name, '/'))
		return (ft_strdup(lst->name));
	if (!(env = get_var(all->my_env, "PATH")))
		return (NULL);
	if (!(split = ft_split(env, ':')))
	{
		free(env);
		return (NULL);
	}
	if (!(res = parse_split_local(split, all, lst)))
	{
		free(env);
		return (free_array(split));
	}
	free_array(split);
	free(env);
	return (res);
}
