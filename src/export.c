/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:44:30 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/19 11:33:17 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	export_normal_helper(t_cmd *cmd, char *key, char *value)
{
	char	*temp;
	t_env	*temp_env;

	temp_env = cmd->env;
	while (temp_env != NULL)
	{
		if (same(key, temp_env->key))
			break ;
		temp_env = temp_env->next;
	}
	if (!temp_env)
		add_node_front(&cmd->env, key, value);
	else
	{
		temp = temp_env->value;
		temp_env->value = value;
		free(temp);
		free(key);
	}
}

static void	export_normal(t_cmd *cmd, char *arg, int *status)
{
	char	*new_env;
	char	*temp1;
	char	*temp2;
	char	*find1;

	new_env = ft_strdup(arg);
	if (!new_env)
		master_clean(NULL, cmd, EXIT_FAILURE);
	find1 = ft_strchr(new_env, '=');
	temp1 = ft_substr(new_env, 0, find1 - new_env);
	if (!temp1)
		master_clean(NULL, cmd, EXIT_FAILURE);
	if (!export_check_key(temp1))
	{
		free(temp1);
		print_export_error(arg, status);
	}
	else
	{
		temp2 = ft_substr(new_env, find1 - new_env + 1, ft_strlen(find1 + 1));
		if (!temp2)
			master_clean(NULL, cmd, EXIT_FAILURE);
		export_normal_helper(cmd, temp1, temp2);
	}
	free(new_env);
}

static void	export_helper(t_cmd *cmd, char *arg, int *status)
{
	t_env	*temp_env;

	temp_env = cmd->env;
	if (!export_check(arg))
		print_export_error(arg, status);
	else if (ft_strchr(arg, '='))
	{
		if (ft_strchr(arg, '=') - (arg) > 0
			&& *(ft_strchr(arg, '=') - 1) == '+')
			export_with_plus(cmd, arg, status);
		else
			export_normal(cmd, arg, status);
	}
	if (temp_env && !cmd->env)
		master_clean(NULL, cmd, EXIT_FAILURE);
}

t_env_pack	run_export(t_cmd *cmd)
{
	t_env_pack	env_pack;
	char		**args;
	int			index;
	int			status;

	status = 0;
	args = cmd->args;
	if (!args[1])
		export_no_arg(cmd);
	else
	{
		index = 1;
		while (args[index])
		{
			export_helper(cmd, args[index], &status);
			index++;
		}
	}
	env_pack.env = cmd->env;
	env_pack.original_env = export_original(cmd->original_env, status);
	return (env_pack);
}

t_env	*export_original(t_env *env, int status)
{
	t_env	*temp_env;
	char	*temp;
	char	*status_str;

	status_str = ft_itoa(status);
	if (!status_str)
		clean_all(env, NULL, NULL, NULL);
	temp_env = env;
	while (temp_env)
	{
		if (same("exit_code", temp_env->key))
			break ;
		temp_env = temp_env->next;
	}
	if (!temp_env)
	{
		temp = ft_strdup("exit_code");
		if (!temp)
			clean_all(env, NULL, status_str, NULL);
		add_node_front(&env, temp, status_str);
		if (!env)
			clean_all(env, NULL, temp, status_str);
	}
	else
	{
		free(temp_env->value);
		temp_env->value = status_str;
	}
	return (env);
}
