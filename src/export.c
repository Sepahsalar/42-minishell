/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:44:30 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/17 20:01:19 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void add_node_front(t_env **env, char *key, char *value)
{
	t_env    *new;

	new = malloc(sizeof(t_env));
	new->key = key;
	new->value = value;
	new->next = *env;
	*env = new;
}

int	run_export(t_cmd *cmd, int original, t_env **env)
{
	// t_env	*env;
	char	**args;
	int		index;
	char	*new_env;
	char	**split;
	char	*temp;

	printf("starting export\n");
	original = 0;
	new_env = NULL;
	args = cmd->args;
	if (args)
	{
		index = 0;
		while (args[index])
		{
			 printf("current arg is %s\n", args[index]);
			if (ft_strchr(args[index], '='))
			{
				new_env = ft_strdup(args[index]);
				// if (new_env == NULL)
				// 	return (1);
				
				split = ft_split(new_env, '=');
				printf("new env is %s and split[0] is %s and split[1] is %s\n", new_env, split[0], split[1]);
				
				// if (original)
				// 	env = cmd->original_env;
				// else
				// 	env = cmd->env;
			//printf("start of env: key is %s and value is %s\n", env->key, env->value);
				while (*env)
				{
					if (ft_strlen(split[0]) == ft_strlen((*env)->key)
						&& !ft_strncmp((*env)->key, split[0], ft_strlen(split[0])))
						break ;
					*env = (*env)->next;
				}
				if (!*env)
				{
					printf("we are doing this\n");
					// if (original)
					// 	add_node_front(&cmd->original_*env, split[0], split[1]);
					// else
					// {
						// *env = cmd->*env;
						printf("This should be here\n");
						add_node_front(env, split[0], split[1]);
						// printf("the key is %s and the value is %s\n", *env->key, *env->value);
						// cmd->*env = *env;
						// printf("the key is %s and the value of cmd_*env is %s\n", cmd->*env->key, cmd->*env->value);
						// printf("the key is %s and the value of next is %s\n", cmd->*env->next->key, cmd->*env->next->value);
					// }
				}
				else
				{
					temp = (*env)->value;
					(*env)->value = ft_strdup(split[1]);
					free(temp);
				}
				free(new_env);
				clean_2d_char(split);
			}
			index++;
		}
		
	}
	return (0);
}
