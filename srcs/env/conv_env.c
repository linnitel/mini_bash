/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 17:21:32 by tisabel           #+#    #+#             */
/*   Updated: 2021/03/16 15:44:09 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		set_env(char *env_i, t_env **temp)
{
	int	n;

	if (ft_strchr(env_i, '='))
	{
		if (((*temp)->name = ft_strcut(env_i, '=')) == NULL)
			return (-1);
		n = ft_strfind(env_i, '=');
		if (((*temp)->value = ft_strdup(&env_i[n])) == NULL)
			return (-1);
	}
	else
	{
		if (((*temp)->name = ft_strdup(env_i)) == NULL)
			return (-1);
	}
	(*temp)->standard = 1;
	return (0);
}

int		convert_env(t_env **env_var, char **env, t_all *all)
{
	int		i;
	t_env	*temp;

	i = 0;
	if (!(temp = init_env()))
		return (ft_error("unset", "out of memory", 12, all));
	*env_var = temp;
	while (env[i] != NULL)
	{
		if (set_env(env[i], &temp) != 0)
			return (ft_error("unset", "out of memory", 12, all));
		if (env[i + 1] == NULL)
			temp->next = NULL;
		else
		{
			if (!(temp->next = init_env()))
				return (ft_error(NULL, "out of memory", 12, all));
			temp = temp->next;
		}
		i++;
	}
	return (0);
}
