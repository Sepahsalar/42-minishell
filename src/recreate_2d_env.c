/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recreate_2d_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:19:09 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/13 17:42:05 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**recreate_2d_env(t_env *env)
{
	int		integer;
	t_env	*temp_env;
	char	**env_2d;
	char	*temp_str;

    // Not sure about this edge case
	if (!env)
	{
		env_2d = (char **)malloc(sizeof(char *));
		env_2d[0] = 0;
		return (env_2d);
	}
	integer = 0;
	temp_env = env;
	while (temp_env)
	{
		integer++;
		temp_env = temp_env->next;
	}
	env_2d = (char **)malloc(sizeof(char *) * (integer + 1));
	env_2d[integer] = 0;
	temp_env = env;
	integer = 0;
	while (temp_env)
	{
		if (!temp_env->key)
			temp_str = ft_strdup("=");
		else
			temp_str = ft_strjoin(temp_env->key, "=");
		if (!temp_str)
			return (0);
		if (temp_env->value)
			env_2d[integer] = ft_strdup(temp_str);
		else
			env_2d[integer] = ft_strjoin(temp_str, temp_env->value);
		free(temp_str);
		if (!env_2d[integer])
			return (0);
		temp_env = temp_env->next;
	}
	return (env_2d);
}
