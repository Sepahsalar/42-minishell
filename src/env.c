/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:40:36 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/20 19:32:16 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env_pack	run_env(t_cmd *cmd)
{
	t_env		*env;
	t_env_pack	env_pack;

	env = cmd->env;
	while (env)
	{
		// printf("%s=%s\n", env->key, env->value);
		ft_putstr_fd(env->key, 1);
		ft_putstr_fd("=", 1);
		ft_putendl_fd(env->value, 1);
		env = env->next;
	}
	env_pack.env = cmd->env;
	env_pack.original_env = cmd->original_env;
	// close(0);
	return (env_pack);
}
