/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazor <mazor@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:25:09 by mazor             #+#    #+#             */
/*   Updated: 2021/03/16 15:44:09 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			clear_redir(t_redir *redir)
{
	int		i;

	i = -1;
	while (redir[++i].r[0])
	{
		if (redir[i].file)
		{
			free(redir[i].file);
			redir[i].file = NULL;
		}
	}
	free(redir);
}

static int		copy_redir_ptr(t_redir *new, t_redir *old)
{
	if (old->file)
	{
		if (!(new->file = ft_strdup(old->file)))
			return (-1);
	}
	else
		new->file = NULL;
	new->r[0] = old->r[0];
	new->r[1] = old->r[1];
	return (0);
}

static t_redir	*realloc_redir(t_redir *old, int n)
{
	t_redir		*new;
	int			i;

	if (!(new = (t_redir *)malloc(sizeof(t_redir) * (n + 2))))
		return (NULL);
	i = -1;
	while (++i < n + 1)
		if (copy_redir_ptr(&new[i], &old[i]) == -1)
			return (NULL);
	new[i].file = NULL;
	new[i].r[0] = '\0';
	new[i].r[1] = '\0';
	clear_redir(old);
	return (new);
}

static char		*get_filename(t_all *all)
{
	char		*file;
	const char	spec[6] = " |;><";

	trim_space(all);
	if (!(file = ft_strdup("")))
		return (NULL);
	while (all->line[all->pos] && !ft_strchr(spec, all->line[all->pos]))
	{
		if (!get_spec(all, &file))
		{
			if (join_char(&file, all->line[all->pos]) == -1)
				return (NULL);
			all->pos++;
		}
	}
	return (file);
}

int				check_redir(t_all *all, t_cmd *lst)
{
	int	n;

	trim_space(all);
	while (all->line[all->pos] == '>' || all->line[all->pos] == '<')
	{
		n = count_redir(lst->redir);
		if (!(lst->redir = realloc_redir(lst->redir, n)))
			return (-1);
		lst->redir[n].r[0] = all->line[all->pos++];
		if (all->line[all->pos] == '>')
			lst->redir[n].r[1] = all->line[all->pos++];
		if (!(lst->redir[n].file = get_filename(all)))
			return (-1);
		trim_space(all);
	}
	return (0);
}
