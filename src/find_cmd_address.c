/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_address.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:31:28 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/19 11:35:15 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	set_cmd_spec(t_cmd *cmd, int exist, int exec, int dir)
{
	cmd->exist = exist;
	cmd->exec = exec;
	cmd->dir = dir;
	return (0);
}

static int	find_cmd_address_d(t_cmd *cmd)
{
	char	*temp_address;

	temp_address = find_address(cmd, 'D');
	if (cmd->error == 1)
		return (1);
	if (temp_address)
	{
		cmd->address = temp_address;
		return (set_cmd_spec(cmd, 0, 0, 1));
	}
	return (0);
}

static int	find_cmd_address_f(t_cmd *cmd)
{
	char	*temp_address;

	temp_address = find_address(cmd, 'F');
	if (cmd->error == 1)
		return (1);
	if (temp_address)
	{
		cmd->address = temp_address;
		return (set_cmd_spec(cmd, 1, 0, 0));
	}
	return (0);
}

static int	find_cmd_address_x(t_cmd *cmd)
{
	char	*temp_address;

	temp_address = find_address(cmd, 'X');
	if (cmd->error == 1)
		return (1);
	if (temp_address)
	{
		cmd->address = temp_address;
		return (set_cmd_spec(cmd, 1, 1, 0));
	}
	else
		if (find_cmd_address_f(cmd))
			return (1);
	return (0);
}

int	find_cmd_address(t_cmd *cmd)
{
	if (cmd->empty_cmd)
	{
		cmd->address = 0;
		return (set_cmd_spec(cmd, 0, 0, 0));
	}
	if (!cmd->cmd_name)
	{
		cmd->address = 0;
		return (set_cmd_spec(cmd, 0, 0, 0));
	}
	else
	{
		if (find_cmd_address_d(cmd))
			return (1);
		if (cmd->address)
			return (0);
		if (find_cmd_address_x(cmd))
			return (1);
	}
	return (0);
}
