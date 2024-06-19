/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:05:16 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/19 12:03:25 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*unset_oldpwd(t_env *env)
{
	t_env	*temp_env;

	temp_env = env;
	while (temp_env && !same(temp_env->key, "OLDPWD"))
		temp_env = temp_env->next;
	if (temp_env)
		env = remove_node(env, temp_env);
	return (env);
}

t_env	*remove_node(t_env *start, t_env *node)
{
	t_env	*temp;
	t_env	*before_node;

	if (node == start)
	{
		start = start->next;
		free(node->key);
		free(node->value);
		free(node);
		return (start);
	}
	temp = start;
	while (temp && temp != node)
	{
		before_node = temp;
		temp = temp->next;
	}
	before_node->next = node->next;
	free(node->key);
	free(node->value);
	free(node);
	return (start);
}

t_env_pack	run_unset(t_cmd *cmd)
{
	t_env_pack	env_pack;
	t_env		*temp;
	char		**args;
	int			index;

	env_pack = init_env_pack(cmd);
	index = 1;
	args = cmd->args;
	while (args[index])
	{
		temp = env_pack.env;
		while (temp)
		{
			if (same(temp->key, args[index]))
				break ;
			temp = temp->next;
		}
		if (temp)
			env_pack.env = remove_node(env_pack.env, temp);
		index++;
	}
	export_original(env_pack.original_env, 0);
	return (env_pack);
}
