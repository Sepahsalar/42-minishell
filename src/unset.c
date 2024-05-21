/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:05:16 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/21 11:58:57 by nnourine         ###   ########.fr       */
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

int	same(char *s1, char *s2)
{
	if (ft_strlen(s1) == ft_strlen(s2) && !ft_strncmp(s1, s2, ft_strlen(s1)))
		return (1);
	return (0);
}

void	*remove_node(t_env *start, t_env *node)
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
	int 		index;

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
	export_orginal(env_pack.original_env, 0);
	return (env_pack);
}
