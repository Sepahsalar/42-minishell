/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:34:31 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/19 14:57:12 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_env	*clean_env_error(t_env *env)
{
	clean_env_list(env);
	return (NULL);
}

static t_env	*fill_env_list_helper(t_env *temp_env, char **envp,
	int index, char **temp)
{
	temp_env->key = ft_strdup(temp[0]);
	temp_env->value = ft_substr(envp[index], ft_strlen(temp[0]) + 1,
		ft_strlen(envp[index] + ft_strlen(temp[0]) + 1));
	return (temp_env);
}

t_env	*fill_env_list(char **envp)
{
	t_env	*env;
	int		env_count;
	int		index;
	char	**temp;
	t_env	*temp_env;

	env_count = char_2d_count(envp);
	env = create_env_list(env_count);
	if (!env)
		return (NULL);
	index = 0;
	temp_env = env;
	while (index < env_count)
	{
		temp = ft_split(envp[index], '=');
		if (!temp)
			return (clean_env_error(env));
		temp_env = fill_env_list_helper(temp_env, envp, index, temp);
		clean_2d_char(temp);
		if (!temp_env->key || !temp_env->value)
			return (clean_env_error(env));
		temp_env = temp_env->next;
		index++;
	}
	return (env);
}
