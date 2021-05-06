/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazor <mazor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:45:35 by mazor             #+#    #+#             */
/*   Updated: 2021/03/17 11:12:14 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_path(t_all *all, char *var_name, char *new_value)
{
	t_env	*temp;

	temp = all->my_env;
	while (temp)
	{
		if (ft_strcmp(temp->name, var_name) == 0)
		{
			free(temp->value);
			if (!(temp->value = new_value))
				return (ft_error("export", "out of memory", 12, all));
			break ;
		}
		temp = temp->next;
	}
	return (0);
}

int			ft_cd(t_all *all, t_cmd *cmd)
{
	char	*path;
	char	*old_path;

	all->exit_status = 0;
	if (cmd->argv[0][0] == '\0')
		path = get_var(all->my_env, "HOME");
	else
		path = ft_strdup(cmd->argv[0]);
	if (path[0] != '\0')
		if (chdir(path) < 0)
		{
			ft_error("cd", "No such file or directory", 1, all);
			free(path);
			return (all->exit_status);
		}
	old_path = get_var(all->my_env, "OLDPWD");
	if (old_path[0] == '\0')
		add_arg(all, "OLDPWD", &all->my_env);
	change_env(all, "OLDPWD", get_var(all->my_env, "PWD"));
	change_path(all, "PWD", getcwd(NULL, _PC_PATH_MAX));
	free(path);
	free(old_path);
	return (all->exit_status);
}
