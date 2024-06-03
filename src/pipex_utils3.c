/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:55:39 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/03 18:59:02 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	output_redirect_builtin_helper(t_cmd *cmd_start,
	t_cmd *cmd_execution, t_last_file *last, t_env_pack env_pack)
{
	t_file		*last_output;

	(void)env_pack;
	last_output = last->file;
	if (last_output->fd_operator <= 2)
	{
		if (last_output->trunc)
			last_output->fd = open(last_output->address,
					O_WRONLY | O_TRUNC, 0644);
		else if (last_output->append)
			last_output->fd = open(last_output->address,
					O_WRONLY | O_APPEND, 0644);
		if (last_output->fd == -1)
			master_clean(0, cmd_start->env, cmd_execution, 1);
		if (dup2(last_output->fd,
				last_output->fd_operator) == -1)
			master_clean(0, cmd_start->env, cmd_execution, 1);
	}
}

void	output_redirect_builtin(t_cmd *cmd_start, t_cmd *cmd_execution,
	t_env_pack env_pack)
{
	t_last_file	*last;

	last = cmd_execution->last_out;
	if (last && !cmd_execution->file_error)
	{
		while (last)
		{
			output_redirect_builtin_helper(cmd_start, cmd_execution,
				last, env_pack);
			last = last->next;
		}
	}
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

static void	output_redirect_helper(t_cmd *cmd_start, t_cmd *cmd_execution,
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
	if (!last || last->file->fd_operator != 1)
		dup2(fd[1], STDOUT_FILENO);
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
