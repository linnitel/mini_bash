/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazor <mazor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 04:10:03 by tisabel           #+#    #+#             */
/*   Updated: 2021/03/17 11:20:22 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		execve_with_pipe(t_all *all, t_cmd *cmd)
{
	char	*fullname;
	char	**argv;
	char	**envp;

	all->exit_status = 0;
	errno = 0;
	envp = deconvert_env(&all->my_env);
	argv = convert_argv(cmd);
	fullname = get_full_cmd_name(all, cmd);
	if (envp && argv && fullname)
	{
		if (execve(fullname, argv, envp) == -1)
			return (ft_error(cmd->name, "permission denied", 13, all));
	}
	return (free_local(envp, argv, &fullname, all->exit_status));
}

void	run_command_pipe(t_all *all, t_cmd *cmd)
{
	int res_cmd;

	res_cmd = start_cmd(all, cmd);
	if (res_cmd < 0)
		all->exit_status = execve_with_pipe(all, cmd);
	restore_fds(all);
	exit(all->exit_status);
}

void	pipe_wait_process(t_all *all, int pipes_len)
{
	int	i;

	i = 0;
	mute_signals();
	while (i < pipes_len)
	{
		waitpid(all->pid[i], &all->res, 0);
		all->exit_status = WEXITSTATUS(all->res);
		i++;
	}
	i = 0;
	while (all->pid[i] != 0 && i < PID_SIZE)
	{
		all->pid[i] = 0;
		i++;
	}
	catch_signals(all);
	implement_signals(all);
	init_signals(all, 'p');
	restore_fds(all);
}

int		redir_pipe(t_all *all, t_cmd **lst, int *fdin, int *fdout)
{
	if ((*lst)->redir->r[0] != '\0')
	{
		if (redir_execute(all, *lst, '<', fdin) != 0 ||
			redir_execute(all, *lst, '>', fdout) != 0)
		{
			restore_fds(all);
			return (all->exit_status);
		}
	}
	if (*fdin >= 0)
	{
		close_dup2_closer(all, *fdin, 0);
		*fdin = -1;
	}
	return (0);
}
