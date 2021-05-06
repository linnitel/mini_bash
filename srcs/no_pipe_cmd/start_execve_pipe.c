/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execve_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazor <mazor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:18:48 by tisabel           #+#    #+#             */
/*   Updated: 2021/03/17 12:12:54 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** support functions for <start_execve> that run the child and parant process
** activities
**
** return: 0 if good, otherwise returns exit status of the failed command
*/

static void	parent_process(int pid, t_all *all)
{
	mute_signals();
	waitpid(pid, &all->res, 0);
	catch_signals(all);
	all->exit_status = all->res;
	implement_signals(all);
	init_signals(all, 'p');
}

static int	child_process(t_all *all, char **envp, char **argv, char *fullname)
{
	init_signals(all, 'c');
	errno = 0;
	all->exit_status = 0;
	if (execve(fullname, argv, envp) == -1)
		all->exit_status = errno;
	return (all->exit_status);
}

/*
** converts environmental variables to the array, checks if the
** command exists and runs the corresponding command
**
** return: 0 if good, otherwise returns exit status of the failed command
*/

int			start_execve(t_all *all, t_cmd *lst)
{
	pid_t		pid;
	char		*fullname;
	char		**envp;
	char		**argv;

	all->exit_status = 0;
	errno = 0;
	envp = deconvert_env(&all->my_env);
	argv = convert_argv(lst);
	fullname = get_full_cmd_name(all, lst);
	if (envp && argv && fullname)
	{
		if ((pid = fork()) == -1)
			ft_error(lst->name, "failed to fork", 13, all);
		else if (pid == 0)
		{
			child_process(all, envp, argv, fullname);
			exit(ft_error(lst->name, strerror(errno), errno, all));
		}
		else
			parent_process(pid, all);
	}
	else
		all->exit_status = 127;
	return (free_local(envp, argv, &fullname, all->exit_status));
}
