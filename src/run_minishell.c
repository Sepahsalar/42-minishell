/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:45:56 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/21 14:33:38 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// t_env_pack	run_minishell(t_cmd *cmd)
// {
// 	t_env_pack	env_pack;
// 	t_env		*env;
// 	int			level;
// 	char		*temp;

// 	env_pack = init_env_pack(cmd);
// 	env = env_pack.env;
// 	while (env && !same(env->key, "SHLVL"))
// 		env = env->next;
// 	if (env)
// 	{
// 		temp = env->value;
// 		level = ft_atoi(env->value);
// 		free(temp);
// 		level = level + 1;
// 		env->value = ft_itoa(level);
// 	}
// 	else
// 		add_node_front(&env_pack.env, "SHLVL", ft_itoa(1));
// 	//should we do anything more than increaing the level?????
// 	export_orginal(env_pack.original_env, 0);
// 	return (env_pack);
// }

t_env	*set_sh_level(t_env *env)
{
	char		*temp_str;
	t_env       *temp_env;

	temp_env = env;
	while (temp_env && !same(temp_env->key, "SHLVL"))
		temp_env = temp_env->next;
	if (temp_env)
	{
		temp_str = temp_env->value;
		temp_env->value = ft_itoa(2);
		free(temp_str);
	}
	else
		add_node_front(&env, "SHLVL", ft_itoa(1));
	return (env);
}
