/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recreate_2d_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:19:09 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/04 11:59:50 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	**allocate_2d_env(t_env *env)
{
	int		index;
	t_env	*temp_env;
	char	**env_2d;

	if (!env)
	{
		env_2d = (char **)malloc(sizeof(char *));
		if (!env_2d)
			return (0);
		env_2d[0] = 0;
		return (env_2d);
	}
	index = 0;
	temp_env = env;
	while (temp_env)
	{
		index++;
		temp_env = temp_env->next;
	}
	env_2d = (char **)malloc(sizeof(char *) * (index + 1));
	if (!env_2d)
		return (0);
	env_2d[index] = 0;
	return (env_2d);
}

static char	**recreate_2d_env_helper(t_env *temp_env, char **env_2d, int index)
{
	char	*temp_str;

	while (temp_env)
	{
		if (!temp_env->key)
			temp_str = ft_strdup("=");
		else
			temp_str = ft_strjoin(temp_env->key, "=");
		if (!temp_str)
			return (0); //it needs to free env_2d
		if (!temp_env->value)
			env_2d[index] = ft_strdup(temp_str);
		else
			env_2d[index] = ft_strjoin(temp_str, temp_env->value);
		free(temp_str);
		if (!env_2d[index])
			return (0); //it needs to free env_2d
		index++;
		temp_env = temp_env->next;
	}
	return (env_2d);
}

char	**recreate_2d_env(t_env *env)
{
	int		index;
	t_env	*temp_env;
	char	**env_2d;

	env_2d = allocate_2d_env(env);
	if (!env_2d)
		return (0);
	temp_env = env;
	index = 0;
	env_2d = recreate_2d_env_helper(temp_env, env_2d, index);
	return (env_2d);
}
