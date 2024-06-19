/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:36:10 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/19 12:36:32 by asohrabi         ###   ########.fr       */
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

	temp_env = cpy_env(cmd->env);
	if (!temp_env)
		master_clean(NULL, cmd, EXIT_FAILURE);
	cpy = handle_oldpwd(temp_env);
	if (!cpy)
		master_clean(NULL, cmd, EXIT_FAILURE);
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
