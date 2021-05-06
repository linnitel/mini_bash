/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 04:07:42 by tisabel           #+#    #+#             */
/*   Updated: 2021/03/16 15:44:09 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			open_file(char redir[2], char *argum)
{
	int fd;

	if (redir[0] == '<')
		fd = open(argum, O_RDONLY, S_IRWXU);
	else
	{
		if (redir[1] == '>')
			fd = open(argum, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
		else
			fd = open(argum, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
	}
	return (fd);
}

int			count_redir(t_redir *redir)
{
	int i;

	i = 0;
	while (redir[i].r[0] != '\0')
		i++;
	return (i);
}

/*
** select the last of the corresponding type redirections,
** opening the files while it dont get to the last
**
** variables: redir_type - the fdin or fdout, redir - type of redirection
** return: 0 if good, otherwise returns exit status of the failed command
*/

int			redir_execute(t_all *all, t_cmd *lst, char redir, int *redir_type)
{
	int i;
	int fd;

	i = 0;
	while (lst->redir[i].r[0] != '\0')
	{
		if (lst->redir[i].r[0] == redir)
		{
			fd = open_file(lst->redir[i].r, lst->redir[i].file);
			if (*redir_type > 0)
				close(*redir_type);
			if (fd < 0)
			{
				restore_fds(all);
				return (ft_error(lst->redir[i].file, strerror(2), 2, all));
			}
			*redir_type = fd;
		}
		i++;
	}
	return (0);
}

/*
** checks for redirections and applys to the corresponding
** type of stream: input or output. If there are no redirections,
** apply the saved stdin or stdout
**
** variables: fd - the fdin or fdout, redir - type of redirection
** return: 0 if good, otherwise returns exit status of the failed command
*/

int			redirections(t_all *all, t_cmd *lst, int *fd, char redir)
{
	if (lst->redir->r[0] != '\0')
	{
		if (redir_execute(all, lst, redir, fd) != 0)
			return (all->exit_status);
	}
	if (*fd < 0)
	{
		if (redir == '<')
			*fd = dup(all->save_fd[0]);
		else
			*fd = dup(all->save_fd[1]);
	}
	return (0);
}
