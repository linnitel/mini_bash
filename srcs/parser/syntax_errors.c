/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazor <mazor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 18:45:43 by mazor             #+#    #+#             */
/*   Updated: 2021/03/16 15:44:09 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	begin_syntax_error(char c)
{
	if (c == '|' || c == '&' || c == ';')
		return (1);
	return (0);
}

static int	trim_quote(char **line)
{
	char	c;
	int		flag;

	flag = 0;
	if (**line == '\'' || **line == '\"')
	{
		c = **line;
		(*line)++;
		flag = 4;
		while (**line)
		{
			if (**line == c && (c == '\'' || *(*line - 1) != '\\'))
			{
				(*line)++;
				return (0);
			}
			else
				(*line)++;
		}
	}
	return (flag);
}

static int	check_semicol_pipe_err(char **line)
{
	if (**line == ';')
	{
		(*line)++;
		trim_space_in_line(line);
		if (**line && **line == ';')
			return (1);
		if (**line && **line == '|')
			return (2);
	}
	if (**line == '|')
	{
		(*line)++;
		trim_space_in_line(line);
		if (**line && **line == '|')
			return (2);
		if (**line && **line == ';')
			return (3);
		if (!(**line))
			return (2);
	}
	return (0);
}

static int	check_redir_err(char **line)
{
	if (**line == '>' || **line == '<')
	{
		(*line)++;
		if (**line == '>')
			(*line)++;
		trim_space_in_line(line);
		if (**line == '\0' || **line == '|' || **line == '>' || **line == '<')
			return (4);
		if (**line == ';')
			return (3);
	}
	return (0);
}

int			check_syntax(t_all *all)
{
	char	*line;
	int		flag;
	char	*temp;

	line = all->line;
	flag = 0;
	if (begin_syntax_error(*line))
		return (ret_err(all, syntax_err_text(line)));
	while (*line)
	{
		temp = line;
		if ((flag = trim_quote(&line)))
			break ;
		if ((flag = check_semicol_pipe_err(&line)))
			break ;
		if ((flag = check_redir_err(&line)))
			break ;
		if ((flag = check_shielding(&line)))
			break ;
		if (*line && line == temp)
			line++;
	}
	if (flag)
		return (ret_err(all, syntax_err_flag_to_text(flag)));
	return (0);
}
