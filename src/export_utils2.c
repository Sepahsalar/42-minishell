/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:54:43 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/03 18:03:02 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	custom_print_export(t_env *temp_env)
{
	int	i;

	i = 0;
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(temp_env->key, 1);
	if (temp_env->value)
	{
		ft_putstr_fd("=\"", 1);
		while (temp_env->value[i])
		{
			if (temp_env->value[i] == '\"')
				ft_putstr_fd("\\\"", 1);
			else
				ft_putchar_fd(temp_env->value[i], 1);
			i++;
		}
		ft_putendl_fd("\"", 1);
	}
	else
		ft_putendl_fd("", 1);
}

void	export_no_arg(t_cmd *cmd)
{
	int		index;
	t_env	*sorted;
	t_env	*cpy;
	int		count;
	t_env	*temp_env;

	cpy = handle_oldpwd(cpy_env(cmd->env));
	sorted = sort_env(cpy);
	index = 1;
	count = env_count(cpy);
	while (index <= count)
	{
		temp_env = sorted;
		while (temp_env && temp_env->index != index)
			temp_env = temp_env->next;
		if (temp_env && !same(temp_env->key, "_"))
			custom_print_export(temp_env);
		index++;
	}
	clean_env_list(cpy);
}

void	print_export_error(char *arg, int *status)
{
	ft_putstr_fd("bash: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("\': not a valid identifier", 2);
	*status = 1;
}

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
	}
}

void	export_with_plus(t_cmd *cmd, char *arg, int *status)
{
	char	*new_env;
	char	*temp1;
	char	*temp2;
	char	*find1;

	new_env = ft_strdup(arg);
	// if (new_env == NULL)
	// 	return (1);
	find1 = ft_strchr(new_env, '=');
	temp1 = ft_substr(new_env, 0, (find1 - new_env - 1));
	if (!export_check_key(temp1))
		print_export_error(arg, status);
	else
	{
		temp2 = ft_substr(new_env, (find1 - new_env) + 1, ft_strlen(find1 + 1));
		export_with_plus_helper(cmd, temp1, temp2);
	}
	free(new_env);
}
