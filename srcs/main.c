/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazor <mazor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 13:35:15 by mazor             #+#    #+#             */
/*   Updated: 2021/03/16 20:45:48 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Zeroes all parameters in the structure t_all
*/

static void	clear(t_all *all)
{
	all->my_env = NULL;
	all->cmd = NULL;
	all->line = NULL;
	all->pos = 0;
	all->res = 1;
	all->semicol = 0;
	all->fdin = -1;
	all->fdout = -1;
	all->exit_status = 0;
	ft_bzero(all->pid, PID_SIZE);
}

/*
** Updates all parameters of the t_all structure to the standard
** ones to get a new line from the user
*/

static void	update_main(t_all *all)
{
	clear_cmd(&all->cmd);
	if (all->semicol == 0)
	{
		free(all->line);
		all->line = NULL;
		all->pos = 0;
	}
	else
	{
		all->semicol = 0;
		all->pos++;
	}
}

/*
** Puts the promt that signifies that you can enter a new command
*/

void		write_promt(t_cmd *lst)
{
	int on_line;
	int echo;

	on_line = 0;
	echo = 1;
	while (lst != NULL)
	{
		echo = strcmp(lst->name, "echo");
		if (echo == 0)
			break ;
		lst = lst->next;
	}
	if (echo == 0)
		if (lst != NULL && strcmp(lst->argv[0], "-n") == 0)
			on_line = 1;
	if (on_line == 0)
		ft_putstr_fd("\b\b  \b\b", 1);
	ft_putstr_fd(PROMPT, 1);
}

/*
** Initialize the main structure, convert environment
** variables to list, init signals
*/

void		init_main(t_all *all, char **env)
{
	clear(all);
	convert_env(&all->my_env, env, all);
	init_signals(all, 'p');
}

/*
** Main function
**
** Executes the cycle of shell that collects data from the terminal,
** executes commands
**
** return: 0 if everything went fine and exit status of the process
** if something went wrong
*/

int			main(int args, char **argv, char **env)
{
	t_all	all;

	(void)args;
	(void)argv;
	init_main(&all, env);
	ft_putstr_fd(PROMPT, 1);
	while (1)
	{
		if (!all.line)
			get_next_line(0, &all.line, &all);
		if (all.line)
		{
			if (!check_syntax(&all))
			{
				parser_string(&all);
				run_cmd(&all);
			}
			if (!all.semicol)
				write_promt(all.cmd);
			update_main(&all);
		}
		else
			write_promt(all.cmd);
	}
}
