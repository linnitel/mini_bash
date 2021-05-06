/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 04:08:33 by tisabel           #+#    #+#             */
/*   Updated: 2021/03/16 15:44:09 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_fds(t_all *all)
{
	all->save_fd[0] = dup(0);
	all->save_fd[1] = dup(1);
}

int		close_dup2_closer(t_all *all, int fd, int std)
{
	close(std);
	return (dup2_closer(all, fd, std));
}

int		dup2_closer(t_all *all, int fd, int std)
{
	if (dup2(fd, std) < 0)
	{
		close(fd);
		return (ft_error("dup2", strerror(errno), errno, all));
	}
	close(fd);
	return (0);
}

void	restore_fds(t_all *all)
{
	close_dup2_closer(all, all->save_fd[0], 0);
	close_dup2_closer(all, all->save_fd[1], 1);
}
