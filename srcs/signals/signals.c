/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:35:29 by tisabel           #+#    #+#             */
/*   Updated: 2021/03/16 15:44:09 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mute_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	catch_signals(t_all *all)
{
	if (WTERMSIG(all->res) > 0 &&
		WTERMSIG(all->res) < 33)
	{
		all->res = WTERMSIG(all->res) + 128;
		return ;
	}
	if (all->res > 0)
		all->res = WEXITSTATUS(all->res);
}

void	implement_signals(t_all *all)
{
	if (all->res == 131)
	{
		ft_putstr_fd("\b\b  \b\b", 1);
		ft_putstr_fd("^\\Quit: 3\n", 1);
	}
	else if (all->res == 130)
	{
		ft_putstr_fd("\b\b", 1);
		ft_putstr_fd("^C\n", 1);
	}
}
