/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:34:31 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/17 17:35:36 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		{
			clean_env_list(env);
			return (NULL);
		}
		temp_env->key = ft_strdup(temp[0]);
		temp_env->value = ft_substr(envp[index], ft_strlen(temp[0]) + 1,
			ft_strlen(envp[index] + ft_strlen(temp[0]) + 1));
		clean_2d_char(temp);
		if (!temp_env->key || !temp_env->value)
		{
			clean_env_list(env);
            return (NULL);
        }
		temp_env = temp_env->next;
		index++;
	}
	return (env);
}
