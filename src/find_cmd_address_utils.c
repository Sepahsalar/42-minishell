/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_address_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:00:12 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/19 11:35:09 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*find_address_abs(t_cmd *cmd, char mode)
{
	char	*address;

	cmd->is_file = 1;
	address = NULL;
	if (check_accessibility(cmd->cmd_name, mode) == 1)
	{
		address = ft_strdup(cmd->cmd_name);
		if (!address)
		{
			cmd->error = 1;
			master_clean(NULL, cmd, EXIT_FAILURE);
		}
	}
	return (address);
}

static char	*find_address_rel(t_cmd *cmd, char mode,
	char **all_path, char *temp)
{
	int		i;
	char	*address;

	i = 0;
	while (all_path[i])
	{
		address = ft_strjoin(all_path[i], temp);
		if (!address)
		{
			cmd->error = 1;
			master_clean(NULL, cmd, EXIT_FAILURE);
		}
		if (check_accessibility(address, mode) == 1)
			return (address);
		free(address);
		i++;
	}
	return (NULL);
}

static t_env	*find_path(t_cmd *cmd)
{
	t_env	*temp_env;

	temp_env = cmd->env;
	while (temp_env && !ft_strnstr(temp_env->key, "PATH", 4))
		temp_env = temp_env->next;
	if (!temp_env)
	{
		cmd->is_file = 1;
		return (0);
	}
	return (temp_env);
}

char	*find_address(t_cmd *cmd, char mode)
{
	char	**all_path;
	char	*address;
	t_env	*temp_env;
	char	*temp;

	if (ft_strchr(cmd->cmd_name, '/'))
		return (find_address_abs(cmd, mode));
	temp = ft_strjoin("/", cmd->cmd_name);
	if (!temp)
	{
		cmd->error = 1;
		master_clean(NULL, cmd, EXIT_FAILURE);
	}
	temp_env = find_path(cmd);
	if (!temp_env)
	{
		free(temp);
		master_clean(NULL, cmd, EXIT_FAILURE);
	}
	all_path = ft_split(temp_env->value, ':');
	if (!all_path)
	{
		cmd->error = 1;
		free(temp);
		master_clean(NULL, cmd, EXIT_FAILURE);
	}
	address = find_address_rel(cmd, mode, all_path, temp);
	free(temp);
	clean_2d_char(all_path);
	return (address);
}
