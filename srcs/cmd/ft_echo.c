/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:39:07 by mazor             #+#    #+#             */
/*   Updated: 2021/03/16 15:44:09 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo(t_all *all, t_cmd *cmd)
{
	int		i;
	char	flag;

	i = -1;
	flag = '\0';
	all->exit_status = 0;
	while (cmd->argv[++i])
	{
		if (i == 0 && !ft_strncmp(cmd->argv[i], "-n", 3))
			flag = 1;
		else
		{
			ft_putstr_fd(cmd->argv[i], 1);
			if (cmd->argv[i + 1] && cmd->argv[i + 1][0] != '\0')
				ft_putchar_fd(' ', 1);
		}
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
	return (all->exit_status);
}
