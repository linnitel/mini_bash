/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazor <mazor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 04:09:35 by tisabel           #+#    #+#             */
/*   Updated: 2021/03/17 11:36:10 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_sighandler(int i)
{
	(void)i;
	ft_putstr_fd("\b\b  \n", 1);
	ft_putstr_fd(PROMPT, 1);
}

void	sigquit_sighandler(int i)
{
	(void)i;
	ft_putstr_fd("\b\b  \b\b", 1);
}

void	init_signals(t_all *all, char c)
{
	extern int	errno;

	errno = 0;
	if (c == 'c')
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else
	{
		signal(SIGINT, sigint_sighandler);
		signal(SIGQUIT, sigquit_sighandler);
		if (errno != 0)
			ft_error(NULL, strerror(errno), errno, all);
	}
}
