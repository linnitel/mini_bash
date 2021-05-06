/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 19:38:32 by mazor             #+#    #+#             */
/*   Updated: 2021/03/16 15:44:09 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir	*init_redir(void)
{
	t_redir *redir;

	if (!(redir = malloc(sizeof(t_redir))))
		return (NULL);
	redir->file = NULL;
	redir->r[0] = '\0';
	redir->r[1] = '\0';
	return (redir);
}

/*
** creates a command structure
**
** return command pointer, otherwise NULL
*/

t_cmd			*init_cmd(void)
{
	t_cmd	*cmd;

	if (!(cmd = malloc(sizeof(t_cmd))))
		return (NULL);
	cmd->name = ft_strdup("");
	if (!(cmd->argv = ft_calloc(2, sizeof(char*))) ||
		!(cmd->argv[0] = ft_strdup(""))
		|| !(cmd->redir = init_redir()))
		return (NULL);
	cmd->pipe = 0;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

/*
** checks that the command is empty
**
** param *lst pointer to command structure
** return 1 if the command is empty, otherwise 0
*/

int				is_null_cmd(t_cmd *lst)
{
	if (!ft_strncmp(lst->name, "", 1))
		return (1);
	return (0);
}
