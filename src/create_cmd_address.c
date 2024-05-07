/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_address.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:31:28 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/07 12:48:53 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_accessibility(char *address, char mode)
{
	int	result;

	if (!address)
		return (0);
	if (mode == 'X')
		result = access(address, X_OK);
	else if (mode == 'R')
		result = access(address, R_OK);
	else if (mode == 'W')
		result = access(address, W_OK);
	else
		result = access(address, F_OK);
	if (result == 0)
		return (1);
	return (0);
}

char	*ft_find_address(t_cmd *cmd, char mode)
{
	char	**all_path;
	char	*address;
	t_env	*temp_env;
	char	*temp;
	int		i;

	// I think it is handled in ft_find_cmd_address
	// if (!cmd->cmd_name)
	// 	return (NULL);
	if (ft_strchr(cmd->cmd_name, '/'))
	{
		if (ft_accessibility(cmd->cmd_name, mode) == 1)
		{
			address = ft_strdup(cmd->cmd_name);
			if (!address)
			{
				cmd->error = 1;
				return (NULL);
			}
			return (address);
		}
		return (NULL);
	}
	temp = ft_strjoin("/", cmd->cmd_name);
	if (!temp)
	{
		cmd->error = 1;
		return (NULL);
	}
	temp_env = cmd->env;
	while (!ft_strnstr(temp_env->key, "PATH", 4))
		temp_env = temp_env->next;
	all_path = ft_split(temp_env->value, ':');
	if (!all_path)
	{
		cmd->error = 1;
		free(temp);
		return (NULL);
	}
	i = 0;
	while (all_path[i])
	{
		address = ft_strjoin(all_path[i], temp);
		if (!address)
		{
			cmd->error = 1;
			free(temp);
			ft_clean_2d_char(all_path);
			return (NULL);
		}
		if (ft_accessibility(address, mode) == 1)
		{
			free(temp);
			ft_clean_2d_char(all_path);
			return (address);
		}
		free (address);
		i++;
	}
	free(temp);
	ft_clean_2d_char(all_path);
	return (0);
}


int	ft_find_cmd_address(t_cmd *cmd)
{
	char	*temp_address;

	if (!cmd->cmd_name)
	{
		cmd->address = 0;
		cmd->exist = 0;
		cmd->exec = 0;
	}
	temp_address = ft_find_address(cmd, 'X');
	if (cmd->error == 1)
		return (1);
	if (temp_address)
	{
		cmd->address = temp_address;
		cmd->exist = 1;
		cmd->exec = 1;
	}
	else
	{
		temp_address = ft_find_address(cmd, 'F');
		if (cmd->error == 1)
			return (1);
		if (temp_address)
		{
			cmd->address = temp_address;
			cmd->exist = 1;
			cmd->exec = 0;
		}
	}
	return (0);
}
