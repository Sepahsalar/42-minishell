/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:34:31 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/15 13:02:33 by nnourine         ###   ########.fr       */
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
	index = 0;
	temp_env = env;
	while (index < env_count)
	{
		temp = ft_split(envp[index], '=');
		// if (!temp)
		// 	master_clean(raw_cmd, env, 0, EXIT_FAILURE);
		temp_env->key = ft_strdup(temp[0]);
		temp_env->value = ft_strdup(temp[1]);
		clean_2d_char(temp);
		// if (!temp_env->key || !temp_env->value)
		// 	master_clean(raw_cmd, env, 0, EXIT_FAILURE);
		temp_env = temp_env->next;
		index++;
	}
	return (env);
}
