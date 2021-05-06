/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:46:57 by mazor             #+#    #+#             */
/*   Updated: 2021/03/16 15:44:09 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			env_cmp(t_env *temp, char *argum)
{
	int		i;
	char	*arg;

	i = 0;
	while (temp)
	{
		arg = ft_strcut(argum, '=');
		if (ft_strncmp(temp->name, arg, ft_strlen(arg) + 1) == 0)
		{
			free(arg);
			return (i);
		}
		i++;
		temp = temp->next;
		free(arg);
	}
	return (-1);
}

int			add_arg(t_all *all, char *argum, t_env **my_env)
{
	int		n;
	int		k;
	t_env	*temp;

	temp = *my_env;
	k = 0;
	if ((check_arg(argum)) != 1)
	{
		if ((n = env_cmp(temp, argum)) != -1)
		{
			while (k < n)
			{
				temp = temp->next;
				k++;
			}
			if (put_value(argum, &temp) != 0)
				return (2);
			temp->standard = 2;
		}
		else
			add_back_env(my_env, creat_env(argum, all));
		return (0);
	}
	return (ft_error("export", "not a valid identifier", 1, all));
}

static void	write_var(t_env env_i)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(env_i.name, 1);
	ft_putstr_fd("= \"", 1);
	ft_putstr_fd(env_i.value, 1);
	ft_putstr_fd("\"\n", 1);
}

void		write_env(t_env **sorted_env)
{
	t_env	*temp;

	temp = *sorted_env;
	while (temp)
	{
		if (temp->standard != 0)
			write_var(*temp);
		temp = temp->next;
	}
}

int			ft_export(t_all *all, t_cmd *cmd)
{
	int		i;
	t_env	*sorted_env;

	i = 0;
	all->exit_status = 0;
	if (ft_strncmp(cmd->argv[0], "", 1) == 0)
	{
		if (!(sorted_env = copy_env(all->my_env)))
			return (ft_error("export", "out of memory", 12, all));
		sort_env(&sorted_env);
		write_env(&sorted_env);
		free_t_env(&sorted_env);
	}
	else
		while (cmd->argv[i] != NULL && cmd->argv[i][0] != '\0')
		{
			if (add_arg(all, cmd->argv[i], &all->my_env) == 2)
				return (ft_error("export", "out of memory", 12, all));
			i++;
		}
	return (all->exit_status);
}
