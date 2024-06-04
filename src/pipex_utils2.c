/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:49:59 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/04 13:15:22 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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

void	input_output_open_helper(t_cmd *cmd_start, t_cmd *cmd_execution,
	t_file *temp_file, t_env_pack env_pack)
{
	(void)env_pack;
	if (temp_file->trunc)
		temp_file->fd = open(temp_file->address,
				O_WRONLY | O_TRUNC, 0644);
	else if (temp_file->append)
		temp_file->fd = open(temp_file->address,
				O_WRONLY | O_APPEND, 0644);
	if (temp_file->fd == -1)
		master_clean(0, cmd_start->env, cmd_execution, 1);
}

void	input_output_open(t_cmd *cmd_start, t_cmd *cmd_execution,
	t_env_pack env_pack)
{
	t_file		*temp_file;

	temp_file = cmd_execution->output;
	while (temp_file)
	{
		input_output_open_helper(cmd_start, cmd_execution, temp_file, env_pack);
		temp_file = temp_file->next;
	}
	temp_file = cmd_execution->input;
	while (temp_file && !temp_file->limiter)
	{
		temp_file->fd = open(temp_file->address, O_RDONLY);
		if (temp_file->fd == -1)
			master_clean(0, cmd_start->env, cmd_execution, 1);
		temp_file = temp_file->next;
	}
}
