/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_temp_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:45:56 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/19 16:28:58 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env_pack	init_env_pack(t_cmd *cmd)
{
	t_env_pack	env_pack;

	env_pack.original_env = cmd->original_env;
	env_pack.env = cmd->env;
	return (env_pack);
}

t_env	*cpy_env(t_env *env)
{
	t_env	*new;
	t_env	*old;
	t_env	*start;

	start = NULL;
	while (env)
	{
		new = malloc(sizeof(t_env));
		if (!new)
			clean_all(start, NULL, NULL, NULL);
		ft_memset(new, 0, sizeof(t_env));
		new->key = ft_strdup(env->key);
		new->value = ft_strdup(env->value);
		if (!new->key || !new->value)
			clean_all(start, NULL, new->key, new->value);
		if (!start)
			start = new;
		else
			old->next = new;
		old = new;
		env = env->next;
	}
	return (start);
}

t_env_pack	run_minishell(t_cmd *cmd)
{
	t_env_pack	env_pack;

	env_pack = init_env_pack(cmd);
	env_pack.original_env = export_original(cmd->original_env, 0);
	return (env_pack);
}

t_env	*set_start(t_env *env)
{
	t_env	*temp_env;

	if (value_finder(env, "SHLVL"))
		env = custom_export(env, "SHLVL", "2");
	else
		env = custom_export(env, "SHLVL", "1");
	temp_env = env;
	while (temp_env && !same(temp_env->key, "OLDPWD"))
		temp_env = temp_env->next;
	if (temp_env)
		env = remove_node(env, temp_env);
	return (env);
}
