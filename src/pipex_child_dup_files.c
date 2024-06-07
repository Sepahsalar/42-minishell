/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_dup_files_child.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:11:01 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/07 14:33:54 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	while (temp_file)
	{
		temp_file->fd = open(temp_file->address, O_RDONLY);
		if (temp_file->fd == -1)
			master_clean(0, cmd_start->env, cmd_execution, 1);
		temp_file = temp_file->next;
	}
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

void	input_redirect(t_cmd *cmd_start, t_cmd *cmd_execution,
	t_env_pack env_pack)
{
	t_file		*last_input;
	t_last_file	*last;

	(void)env_pack;
	last = cmd_execution->last_in;
	if (last && !cmd_execution->file_error)
	{
		while (last)
		{
			last_input = last->file;
			if (last_input->fd_operator <= 2)
			{
				if (dup2(last_input->fd, last_input->fd_operator) == -1)
					master_clean(0, cmd_start->env, cmd_execution, 1);
				close(last_input->fd);
			}
			last = last->next;
		}
	}
}

void	output_redirect(t_cmd *cmd_start, t_cmd *cmd_execution,
	t_env_pack env_pack, int fd[2])
{
	t_last_file	*last;

	last = cmd_execution->last_out;
	if (last && !cmd_execution->file_error)
		output_redirect_helper(cmd_start, cmd_execution, env_pack, fd);
	else if (cmd_count(cmd_start) > cmd_execution->index
		&& !cmd_execution->file_error)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			master_clean(0, cmd_start->env, cmd_execution, 1);
	}
}

void	output_redirect_helper(t_cmd *cmd_start, t_cmd *cmd_execution,
	t_env_pack env_pack, int fd[2])
{
	t_file		*last_output;
	t_last_file	*last;

	(void)env_pack;
	last = cmd_execution->last_out;
	while (last)
	{
		last_output = last->file;
		if (last_output->fd_operator <= 2)
		{
			if (dup2(last_output->fd,
					last_output->fd_operator) == -1)
				master_clean(0, cmd_start->env, cmd_execution, 1);
		}
		last = last->next;
	}
	last = cmd_execution->last_out;
	while (last && last->file->fd_operator != 1)
		last = last->next;
	if ((!last || last->file->fd_operator != 1)
		&& (cmd_count(cmd_start) > cmd_execution->index))
		dup2(fd[1], STDOUT_FILENO);
}
