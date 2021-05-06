/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:48:09 by tisabel           #+#    #+#             */
/*   Updated: 2021/03/16 15:44:09 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** creates an enviroment variables structure
**
** return env pointer, otherwise NULL
*/

t_env	*init_env(void)
{
	t_env	*my_env;

	if (!(my_env = malloc(sizeof(t_env))))
		return (NULL);
	my_env->name = NULL;
	my_env->value = NULL;
	my_env->standard = 0;
	my_env->next = NULL;
	return (my_env);
}

int		copy_var(t_env *from, t_env *new)
{
	if (!(new->name = ft_strdup(from->name))
		|| !(new->value = ft_strdup(from->value)))
	{
		free_t_env(&new);
		return (0);
	}
	new->standard = from->standard;
	return (1);
}

t_env	*copy_env(t_env *my_env)
{
	t_env	*copy;
	t_env	*temp;
	t_env	*begin;

	temp = my_env;
	if (!(copy = init_env()))
		return (NULL);
	if (copy_var(temp, copy) == 0)
		return (NULL);
	begin = copy;
	while (temp)
	{
		temp = temp->next;
		if (temp != NULL)
		{
			if (!(copy->next = init_env()))
				return (NULL);
			copy = copy->next;
			if (copy_var(temp, copy) == 0)
				return (NULL);
		}
	}
	return (begin);
}

void	swap_envs(t_env **begin, t_env *my_env)
{
	t_env *temp;

	temp = *begin;
	if (*begin != my_env)
	{
		while (temp->next != my_env)
			temp = temp->next;
		temp->next = my_env->next;
		my_env->next = my_env->next->next;
		temp->next->next = my_env;
	}
	else
	{
		*begin = temp->next;
		temp->next = temp->next->next;
		(*begin)->next = temp;
	}
}

void	sort_env(t_env **my_env)
{
	t_env	*temp;
	int		len;
	int		i;

	i = 0;
	len = count_env(*my_env);
	while (i < len - 1)
	{
		temp = *my_env;
		while (temp->next)
		{
			if (ft_strcmp(temp->name, temp->next->name) > 0)
			{
				swap_envs(my_env, temp);
			}
			else
				temp = temp->next;
		}
		i++;
	}
}
