/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:40:36 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/20 15:39:54 by asohrabi         ###   ########.fr       */
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
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	env_pack.env = cmd->env;
	env_pack.original_env = cmd->original_env;
	return (env_pack);
}
