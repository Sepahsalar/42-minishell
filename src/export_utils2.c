/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:54:43 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/19 12:38:28 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	export_with_plus_helper(t_cmd *cmd, char *key, char *value)
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
		temp_env->value = ft_strjoin(temp, value);
		free(temp);
		free(key);
		free(value);
		if (!temp_env->value)
			master_clean(NULL, cmd, EXIT_FAILURE);
	}
}

static void	process_export_key(t_cmd *cmd, char *new_env,
	char *find1, char *temp1)
{
	char	*temp2;

	temp2 = ft_substr(new_env, (find1 - new_env) + 1, ft_strlen(find1 + 1));
	if (!temp2)
		master_clean(NULL, cmd, EXIT_FAILURE);
	export_with_plus_helper(cmd, temp1, temp2);
}

void	export_with_plus(t_cmd *cmd, char *arg, int *status)
{
	char	*new_env;
	char	*temp1;
	char	*find1;

	new_env = ft_strdup(arg);
	if(!new_env)
		master_clean(NULL, cmd, EXIT_FAILURE);
	find1 = ft_strchr(new_env, '=');
	temp1 = ft_substr(new_env, 0, (find1 - new_env - 1));
	if (!temp1)
	{
		free(new_env);
		master_clean(NULL, cmd, EXIT_FAILURE);
	}
	if (!export_check_key(temp1))
	{
		free(temp1);
		print_export_error(arg, status);
	}
	else
		process_export_key(cmd, new_env, find1, temp1);
	free(new_env);
}
