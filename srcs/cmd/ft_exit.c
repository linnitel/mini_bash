/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 18:38:00 by mazor             #+#    #+#             */
/*   Updated: 2021/03/17 10:38:39 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		arg_len(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->argv[i] != NULL)
		i++;
	return (i - 1);
}

int		check_digit(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) != 1)
			return (0);
		i++;
	}
	return (1);
}

/*
** executes the exit command
**
** param *all general structure
** param *cmd command structure
** return exitstatus
*/

int		ft_exit(t_all *all, t_cmd *cmd)
{
	int				n;
	unsigned char	exit_status;

	n = arg_len(cmd);
	exit_status = all->exit_status;
	ft_putstr_fd("exit\n", 1);
	if (n > 1 || (check_digit(cmd->argv[0]) != 1 && cmd->argv[0][0] != '-')
	|| (cmd->argv[0][0] == '-' && ft_isdigit(cmd->argv[0][1]) != 1))
	{
		if (check_digit(cmd->argv[0]) != 1)
			ft_error("exit", "numeric argument required", 255, all);
		else
			ft_error("exit", "too many arguments", 1, all);
		exit_status = (unsigned char)all->exit_status;
	}
	else
	{
		if (n == 1)
			exit_status = (unsigned char)ft_atoi(cmd->argv[0]);
	}
	free_t_env(&all->my_env);
	restore_fds(all);
	clear_all(all);
	exit(exit_status);
}
