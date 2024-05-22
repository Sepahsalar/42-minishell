/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:44:30 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/22 09:23:10 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// handle this declare -x OLDPWD="\"nima\"" after fixing handle quote
// also delete this "declare -x _="/Users/nnourine/Hive/minishell/42-minishell/./minishell""
// error handling for export

void	add_node_front(t_env **env, char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->key = key;
	new->value = value;
	new->next = *env;
	*env = new;
}

//probably original should be removed from the input
// t_env_pack	run_export(t_cmd *cmd, int original)
// {
// 	t_env		*temp_env;
// 	t_env_pack	env_pack;
// 	char		**args;
// 	int			index;
// 	char		*new_env;
// 	char		**split;
// 	char		*temp;

// 	original = 0;
// 	new_env = NULL;
// 	args = cmd->args;
// 	if (args)
// 	{
// 		index = 0;
// 		while (args[index])
// 		{
// 			if (ft_strchr(args[index], '='))
// 			{
// 				new_env = ft_strdup(args[index]);
// 				// if (new_env == NULL)
// 				// 	return (1);
// 				split = ft_split(new_env, '=');
// 				if (original)
// 					temp_env = cmd->original_env;
// 				else
// 					temp_env = cmd->env;
// 				while (temp_env != NULL)
// 				{
// 					if (ft_strlen(split[0]) == ft_strlen(temp_env->key)
// 						&& !ft_strncmp(temp_env->key, split[0],
// 							ft_strlen(split[0])))
// 						break ;
// 					temp_env = temp_env->next;
// 				}
// 				if (!temp_env)
// 				{
// 					if (original)
// 						add_node_front(&cmd->original_env, split[0], split[1]);
// 					else
// 						add_node_front(&cmd->env, split[0], split[1]);
// 				}
// 				else
// 				{
// 					temp = temp_env->value;
// 					temp_env->value = ft_strdup(split[1]);
// 					free(temp);
// 				}
// 				free(new_env);
// 				// clean_2d_char(split);
// 			}
// 			index++;
// 		}
// 	}
// 	env_pack.env = cmd->env;
// 	env_pack.original_env = cmd->original_env;
// 	env_pack.original_env = export_orginal(env_pack.original_env, 0); // instead of 0 it should be the correct exit code
// 	return (env_pack);
// }

int	is_higher(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 < *s2)
			return (*s2 - *s1);
		if (*s1 > *s2)
			return (*s2 - *s1);
		else
		{
			s1++;
			s2++;
		}
	}
	return (*s2 - *s1);
}

int	env_count(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}


t_env	*sort_env(t_env *env)
{
	int		index;
	int		count;
	t_env	*temp_index;
	t_env	*temp;

	index = 1;
	count = env_count(env);
	printf("env_count: %d\n", count);
	while (index <= count)
	{
		printf("index: %d\n", index);
		temp = env;
		while (temp && temp->index)
			temp = temp->next;
		printf("middle\n");
		temp_index = temp;
		temp = env;
		while (temp)
		{
			if (temp && temp_index && is_higher(temp_index->key, temp->key) < 0
				&& !temp->index)
				temp_index = temp;
			temp = temp->next;
		}
		printf("end\n");
		if (temp_index)
			temp_index->index = index;
		index++;
	}
	return (env);
}

t_env	*handle_oldpwd(t_env *env)
{
	t_env	*temp;
	int		has_oldpwd;

	has_oldpwd = 0;
	temp = env;
	while (temp)
	{
		if (same(temp->key, "OLDPWD"))
			has_oldpwd = 1;
		temp = temp->next;
	}
	if (!has_oldpwd)
		add_node_front(&env, ft_strdup("OLDPWD"), NULL);
	return (env);
}

t_env_pack	run_export(t_cmd *cmd)
{
	t_env		*temp_env;
	t_env_pack	env_pack;
	char		**args;
	int			index;
	char		*new_env;
	char		**split;
	char		*temp;
	int			status;
	t_env       *sorted;
	t_env 		*cpy;
	int			count;

	new_env = NULL;
	status = 0;
	args = cmd->args;
	if (!args[1])
	{
		cpy = handle_oldpwd(cpy_env(cmd->env));
		sorted = sort_env(cpy);
		index = 1;
		count = env_count(cpy);
		while (index <= count)
		{
			temp_env = sorted;
			while (temp_env && temp_env->index != index)
				temp_env = temp_env->next;
			if (temp_env)
			{
				printf("declare -x %s", temp_env->key);
				if (temp_env->value)
					printf("=\"%s\"\n", temp_env->value);
				else
					printf("\n");
			}
			index++;
		}
		clean_env_list(cpy);
	}
	else
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
					add_node_front(&cmd->env, split[0], split[1]);
				else
				{
					temp = temp_env->value;
					temp_env->value = ft_strdup(split[1]);
					free(temp);
				}
				free(new_env);
				//clean_2d_char(split);
			}
			index++;
		}
	}
	env_pack.env = cmd->env;
	// env_pack.original_env = cmd->original_env;
	env_pack.original_env = export_original(cmd->original_env, status); // instead of 0 it should be the correct exit code
	return (env_pack);
}

t_env	*export_original(t_env *env, int status)
{
	t_env	*temp_env;
	char	*temp;
	char	*status_str;

	temp_env = env;
	while (temp_env)
	{
		if (ft_strlen("exit_code") == ft_strlen(temp_env->key)
			&& !ft_strncmp(temp_env->key, "exit_code",
				ft_strlen("exit_code")))
			break ;
		temp_env = temp_env->next;
	}
	status_str = ft_itoa(status);
	if (!temp_env)
		add_node_front(&env, "exit_code", status_str);
	else
	{
		temp = temp_env->value;
		temp_env->value = status_str;
		free(temp);
	}
	return (env);
}
