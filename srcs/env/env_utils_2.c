/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:45:55 by tisabel           #+#    #+#             */
/*   Updated: 2021/03/16 15:44:09 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_last(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next)
		env = env->next;
	return (env);
}

void	add_back_env(t_env **my_env, t_env *new_env)
{
	t_env	*res;

	if (my_env && new_env)
	{
		if (!(*my_env))
			*my_env = new_env;
		else
		{
			res = env_last(*my_env);
			res->next = new_env;
		}
	}
}

t_env	*creat_env(char *argum, t_all *all)
{
	t_env	*temp;

	if (!(temp = init_env()))
	{
		ft_error("unset", "out of memory", 12, all);
		return (NULL);
	}
	if (ft_strfind(argum, '=') != 0)
	{
		temp->name = ft_strcut(argum, '=');
		temp->value = ft_strdup(ft_strnstr(argum, "=", ft_strlen(argum)) + 1);
	}
	else
	{
		temp->name = ft_strdup(argum);
		temp->value = ft_strdup("");
	}
	temp->standard = 2;
	return (temp);
}

int		change_env(t_all *all, char *var_name, char *new_value)
{
	t_env *temp;

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

int		count_env(t_env *my_env)
{
	int	len;

	len = 0;
	while (my_env)
	{
		len++;
		my_env = my_env->next;
	}
	return (len);
}
