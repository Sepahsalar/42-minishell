/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:44:30 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/20 15:46:18 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_node_front(t_env **env, char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->key = key;
	new->value = value;
	new->next = *env;
	*env = new;
}

t_env_pack	run_export(t_cmd *cmd, int original)
{
	t_env		*temp_env;
	t_env_pack	env_pack;
	char		**args;
	int			index;
	char		*new_env;
	char		**split;
	char		*temp;

	original = 0;
	new_env = NULL;
	args = cmd->args;
	if (args)
	{
		index = 0;
		while (args[index])
		{
			if (ft_strchr(args[index], '='))
			{
				new_env = ft_strdup(args[index]);
				// if (new_env == NULL)
				// 	return (1);
				split = ft_split(new_env, '=');
				if (original)
					temp_env = cmd->original_env;
				else
					temp_env = cmd->env;
				while (temp_env != NULL)
				{
					if (ft_strlen(split[0]) == ft_strlen(temp_env->key)
						&& !ft_strncmp(temp_env->key, split[0],
							ft_strlen(split[0])))
						break ;
					temp_env = temp_env->next;
				}
				if (!temp_env)
				{
					if (original)
						add_node_front(&cmd->original_env, split[0], split[1]);
					else
						add_node_front(&cmd->env, split[0], split[1]);
				}
				else
				{
					temp = temp_env->value;
					temp_env->value = ft_strdup(split[1]);
					free(temp);
				}
				free(new_env);
				// clean_2d_char(split);
			}
			index++;
		}
	}
	env_pack.env = cmd->env;
	env_pack.original_env = cmd->original_env;
	return (env_pack);
}
