/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 14:01:03 by mazor             #+#    #+#             */
/*   Updated: 2021/03/16 15:44:09 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_gnl_exit(t_all *all)
{
	ft_putstr_fd("exit\n", 1);
	free_t_env(&all->my_env);
	clear_all(all);
	exit(all->exit_status);
}

static int		check_ret(int ret, char **line, t_all *all)
{
	if (ret == 0)
	{
		if (ft_strcmp(*line, "") == 0)
			ft_gnl_exit(all);
		else
		{
			ft_putstr_fd("  \b\b", 1);
			return (1);
		}
	}
	return (0);
}

static int		set_read(int fd, char **line, t_all *all)
{
	int		ret;
	char	buf[2];

	while ((ret = read(fd, buf, 1)) >= 0)
	{
		if (check_ret(ret, line, all))
			continue ;
		buf[1] = 0;
		if (buf[0] == '\n')
			break ;
		if (!*line)
		{
			if (!(*line = ft_strdup("")))
				return (-1);
		}
		if (!(*line = ft_strjoin(*line, buf)))
			return (-1);
	}
	return (1);
}

int				get_next_line(int fd, char **line, t_all *all)
{
	if (fd < 0 || !line)
		return (-1);
	if (set_read(fd, line, all) == -1)
		return (-1);
	return (1);
}
