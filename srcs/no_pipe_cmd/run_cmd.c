/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 21:20:05 by mazor             #+#    #+#             */
/*   Updated: 2021/03/16 15:44:09 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** clears strings created for the execve
**
** return: 0 if good, otherwise returns exit status of the failed command
*/

int			free_local(char **array_1, char **array_2, char **text, int ret)
{
	if (array_1)
		free_array(array_1);
	if (array_2)
		free_array(array_2);
	if (*text)
	{
		free(*text);
		*text = NULL;
	}
	return (ret);
}

/*
** checks if it is a build in or external command and starts
** the corresponding execution
**
** return: 0 if good, otherwise returns exit status of the failed command
*/

int			exec_command(t_all *all, t_cmd *cmd)
{
	int res_cmd;

	if ((res_cmd = start_cmd(all, cmd)) > 0)
		return (all->exit_status);
	if (res_cmd == -1)
		start_execve(all, cmd);
	return (all->exit_status);
}

void		reset_in_out(int *fdin, int *fdout)
{
	if (*fdin >= 0)
	{
		close(*fdin);
		*fdin = -1;
	}
	if (*fdout >= 0)
	{
		close(*fdout);
		*fdout = -1;
	}
}

/*
** execute the command
**
** return: 0 if good, otherwise returns exit status of the failed command
*/

int			run_cmd(t_all *all)
{
	t_cmd	*lst;
	int		fdin;
	int		fdout;

	lst = all->cmd;
	fdin = -1;
	fdout = -1;
	if (lst && (!is_null_cmd(lst) || lst->redir->r[0] != '\0'))
	{
		save_fds(all);
		if (lst->pipe == 1)
			exec_command_pipe(all, &lst);
		else
		{
			if (redirections(all, lst, &fdin, '<') == 0 &&
			redirections(all, lst, &fdout, '>') == 0 &&
			close_dup2_closer(all, fdin, 0) == 0 &&
			close_dup2_closer(all, fdout, 1) == 0 && !is_null_cmd(lst))
				exec_command(all, lst);
			else
				reset_in_out(&fdin, &fdout);
			restore_fds(all);
		}
	}
	return (all->exit_status);
}
