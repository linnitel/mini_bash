/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 04:10:03 by tisabel           #+#    #+#             */
/*   Updated: 2021/03/16 15:44:09 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	child_process(t_all *all, t_cmd **lst, int *fdout)
{
	close(1);
	if ((*lst)->pipe == 1)
	{
		close((*lst)->fd_pipe[0]);
		dup2_closer(all, (*lst)->fd_pipe[1], 1);
	}
	else
		dup2(all->save_fd[1], 1);
	if (*fdout >= 0)
	{
		close_dup2_closer(all, *fdout, 1);
		*fdout = -1;
	}
	init_signals(all, 'c');
	run_command_pipe(all, *lst);
	return (0);
}

static int	parent_process_pipe(t_all *all, t_cmd **lst, int *fdout)
{
	close(0);
	if ((*lst)->pipe == 1)
	{
		close((*lst)->fd_pipe[1]);
		dup2_closer(all, (*lst)->fd_pipe[0], 0);
	}
	else
		dup2(all->save_fd[0], 0);
	if (*fdout >= 0)
	{
		close(*fdout);
		*fdout = -1;
	}
	return (0);
}

static int	wrong_pid(t_all *all, t_cmd **lst)
{
	restore_fds(all);
	return (ft_error((*lst)->name, "failed to fork", 13, all));
}

int			exec_command_pipe(t_all *all, t_cmd **lst)
{
	int	i;

	i = 0;
	while (*lst)
	{
		if (!is_null_cmd(*lst) || (*lst)->redir->r[0] != '\0')
		{
			if (redir_pipe(all, lst, &all->fdin, &all->fdout) != 0)
				return (all->exit_status);
			if ((*lst)->pipe == 1)
				pipe((*lst)->fd_pipe);
			all->pid[i] = fork();
			if (all->pid[i] < 0)
				wrong_pid(all, lst);
			if (all->pid[i] == 0)
				child_process(all, lst, &all->fdout);
			if (all->pid[i] > 0)
				parent_process_pipe(all, lst, &all->fdout);
			*lst = (*lst)->next;
			i++;
		}
	}
	pipe_wait_process(all, i);
	return (all->exit_status);
}
