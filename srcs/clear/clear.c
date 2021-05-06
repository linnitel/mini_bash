/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 19:39:57 by mazor             #+#    #+#             */
/*   Updated: 2021/03/16 17:31:19 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Clears the entire t_cmd structure
**
** param **lst Pointer to sheet of structure t_cmd
*/

void	free_null(char *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	clear_cmd(t_cmd **cmd_lst)
{
	t_cmd	*tmp;
	t_cmd	*save;
	int		i;

	if (cmd_lst)
	{
		tmp = *cmd_lst;
		while (tmp)
		{
			save = tmp->next;
			i = -1;
			if (tmp->name)
				free_null(tmp->name);
			if (tmp->argv)
			{
				while (tmp->argv[++i])
					free(tmp->argv[i]);
			}
			free(tmp->argv);
			clear_redir(tmp->redir);
			free(tmp);
			tmp = save;
		}
		*cmd_lst = NULL;
	}
}

/*
** Clears the entire t_all structure
**
** param *all general structure
*/

int		clear_all(t_all *all)
{
	clear_cmd(&all->cmd);
	free(all->line);
	return (all->exit_status);
}

/*
** Clears an array of strings
**
** param **text Pointer to array of strings
*/

void	*free_array(char **text)
{
	int		i;

	i = -1;
	if (text)
	{
		if (*text)
		{
			while (text[++i])
			{
				free(text[i]);
				text[i] = NULL;
			}
		}
		free(text);
		text = NULL;
	}
	return (NULL);
}
