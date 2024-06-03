/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:44:25 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/03 18:49:36 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static t_env_pack	output_check_create(t_cmd *cmd_start, t_cmd *cmd_execution,
	t_file *temp_file, t_env_pack env_pack)
{
	if (temp_file->trunc)
		temp_file->fd = open(temp_file->address,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (temp_file->append)
		temp_file->fd = open(temp_file->address,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (temp_file->fd == -1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(temp_file->address, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		master_clean(0, cmd_start->env, cmd_execution, -1);
		env_pack.original_env
			= export_original(env_pack.original_env, 1);
		cmd_execution->file_error = 1;
	}
	return (env_pack);
}

static t_env_pack	input_check(t_cmd *cmd_start, t_cmd *cmd_execution,
	t_file *temp_file, t_env_pack env_pack)
{
	if (!temp_file->limiter && !temp_file->ignore)
	{
		temp_file->fd = open(temp_file->address, O_RDONLY);
		if (temp_file->fd == -1)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(temp_file->address, 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd(strerror(errno), 2);
			master_clean(0, cmd_start->env, cmd_execution, -1);
			env_pack.original_env
				= export_original(env_pack.original_env, 1);
			cmd_execution->file_error = 1;
		}
	}
	return (env_pack);
}

t_env_pack	input_output_check_create(t_cmd *cmd_start, t_cmd *cmd_execution,
	t_env_pack env_pack)
{
	t_file		*temp_file;

	temp_file = cmd_execution->all;
	while (temp_file)
	{
		if (temp_file->input)
			env_pack = input_check(cmd_start, cmd_execution,
					temp_file, env_pack);
		else if (temp_file->trunc || temp_file->append)
			env_pack = output_check_create(cmd_start, cmd_execution,
					temp_file, env_pack);
		if (temp_file->fd == -1)
			break ;
		// close(temp_file->fd);
		temp_file = temp_file->next;
	}
	return (env_pack);
}

t_env_pack	empty_cmd_check(t_cmd *cmd_start, t_cmd *cmd_execution,
	t_env_pack env_pack)
{
	(void)cmd_start;
	if (cmd_execution->cmd_name == NULL
		|| (*cmd_execution->cmd_name == '\0' && cmd_execution->empty_cmd != 1))
	{
		env_pack.original_env = export_original(env_pack.original_env, 0);
		cmd_execution->file_error = 1;
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
