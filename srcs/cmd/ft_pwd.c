/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:43:41 by mazor             #+#    #+#             */
/*   Updated: 2021/03/17 10:47:27 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** executes the pwd command
**
** param *all general structure
** param *cmd command structure
** return 0 if good, otherwise exitstatus of the program (errno number)
*/

int		ft_pwd(t_all *all, t_cmd *cmd)
{
	char		*pwd;
	extern int	errno;

	(void)cmd;
	all->exit_status = 0;
	errno = 0;
	if (!(pwd = getcwd(NULL, _PC_PATH_MAX)))
		ft_error("pwd", strerror(errno), errno, all);
	else
		ft_putendl_fd(pwd, 1);
	free(pwd);
	return (all->exit_status);
}
