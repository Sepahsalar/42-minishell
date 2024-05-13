/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_package.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:47:01 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/13 17:44:36 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execution_package(t_cmd *cmd,
	char **cmd_address, char ***cmd_args, char ***cmd_env)
{
	if (cmd)
	{
		*cmd_address = ft_strdup(cmd->address);
		*cmd_args = copy_2d_char(cmd->args);
		*cmd_env = recreate_2d_env(cmd->env);
		if (!cmd_address ||!cmd_args ||!cmd_env)
			cmd->error = 1;
	}
}
