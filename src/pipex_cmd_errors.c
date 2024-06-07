/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_cmd_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:15:35 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/07 18:54:32 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env_pack	full_cmd_check(t_cmd *cmd_start, t_cmd *cmd_execution,
	t_env_pack env_pack)
{
	if ((!cmd_execution->exec || cmd_execution->dir)
		&& is_builtin(cmd_execution) == -1 && !cmd_execution->file_error)
	{
		if (cmd_execution->dir)
			env_pack = cmd_dir(cmd_start, cmd_execution, env_pack);
		else
		{
			if (cmd_execution->exist)
				env_pack = cmd_permission(cmd_start, cmd_execution, env_pack);
			else
				env_pack = cmd_not_found(cmd_start, cmd_execution, env_pack);
		}
	}
	return (env_pack);
}

t_env_pack	cmd_dir(t_cmd *cmd_start, t_cmd *cmd_execution, t_env_pack env_pack)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd_execution->cmd_name, 2);
	ft_putendl_fd(": is a directory", 2);
	master_clean(0, cmd_start->env, cmd_execution, -1);
	env_pack.original_env = export_original(env_pack.original_env, 126);
	cmd_execution->file_error = 1;
	return (env_pack);
}

t_env_pack	cmd_permission(t_cmd *cmd_start, t_cmd *cmd_execution,
	t_env_pack env_pack)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd_execution->cmd_name, 2);
	ft_putendl_fd(": Permission denied", 2);
	master_clean(0, cmd_start->env, cmd_execution, -1);
	env_pack.original_env
		= export_original(env_pack.original_env, 126);
	cmd_execution->file_error = 1;
	return (env_pack);
}

t_env_pack	cmd_not_found(t_cmd *cmd_start, t_cmd *cmd_execution,
	t_env_pack env_pack)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd_execution->cmd_name, 2);
	if (cmd_execution->is_file)
		ft_putendl_fd(": No such file or directory", 2);
	else
		ft_putendl_fd(": command not found", 2);
	master_clean(0, cmd_start->env, cmd_execution, -1);
	env_pack.original_env
		= export_original(env_pack.original_env, 127);
	cmd_execution->file_error = 1;
	return (env_pack);
}
