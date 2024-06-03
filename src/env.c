/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:40:36 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/03 13:44:49 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env_pack	run_env(t_cmd *cmd)
{
	t_env		*env;
	t_env_pack	env_pack;

	env_pack = init_env_pack(cmd);
	env = cmd->env;
	while (env)
	{
		ft_putstr_fd(env->key, 1);
		ft_putstr_fd("=", 1);
		ft_putendl_fd(env->value, 1);
		env = env->next;
	}
	export_original(env_pack.original_env, 0);
	return (env_pack);
}
