/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:56:47 by asohrabi          #+#    #+#             */
/*   Updated: 2024/05/20 16:11:35 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
// test just clear command
t_env_pack	execute_cmd(t_cmd *cmd_start, t_cmd *cmd_execution)
{
	char		*cmd_address;
	char		**cmd_args;
	char		**cmd_env;
	t_file		*temp_file;
	t_file		*last_input;
	t_file		*last_output;
	t_last_file	*last;
	int			fd[2];
	pid_t		pid;
	int     	status;
	int			index;
	t_env_pack	env_pack;

	status = 0;
	last_input = NULL;
	last_output = NULL;
	env_pack.env = cmd_execution->env;
	env_pack.original_env = cmd_execution->original_env;
	temp_file = cmd_execution->input;
	while (temp_file)
	{
		if (temp_file->read == 0 && !temp_file->limiter)
		{
			if (temp_file->exist == 0)
			{
				printf("bash: %s: No such file or directory\n",
					temp_file->address);
				master_clean(0, cmd_start->env, cmd_start, -1);
				// return (1);
			}
			else
			{
				printf("bash: %s: Permission denied\n", temp_file->address);
				master_clean(0, cmd_start->env, cmd_start, -1);
				// return (1);
			}
		}
		temp_file = temp_file->next;
	}
	temp_file = cmd_execution->output;
	while (temp_file)
	{
		if (temp_file->trunc)
			temp_file->fd = open(temp_file->address,
					O_RDWR | O_CREAT | O_TRUNC, 0644);
		else if (temp_file->append)
			temp_file->fd = open(temp_file->address,
					O_RDWR | O_CREAT | O_APPEND, 0644);
		if (temp_file->fd == -1)
		{
			master_clean(0, cmd_start->env, cmd_execution, -1);
			// return (1);
		}
		close(temp_file->fd);
		temp_file = temp_file->next;
	}
	// if (cmd_execution->cmd_name == NULL || *cmd_execution->cmd_name == '\0')
	// 	// return (0);
	if (cmd_execution->exec == 0 && is_builtin(cmd_execution) == -1)
	{
		if (cmd_execution->exist)
		{
			printf("bash: %s: Permission denied\n",
				cmd_execution->cmd_name);
			master_clean(0, cmd_start->env, cmd_execution, -1);
			// return (126);
		}
		else
		{
			printf("bash: %s: command not found\n",
				cmd_execution->cmd_name);
			master_clean(0, cmd_start->env, cmd_execution, -1);
			// return (127);
		}
	}
	if (cmd_count(cmd_start) == 1 && (is_builtin(cmd_execution) == 4 || is_builtin(cmd_execution) == 5))
	{
		env_pack = run_builtin(cmd_execution);
	}
	else if (is_builtin(cmd_execution) != 4 || is_builtin(cmd_execution) != 5)
	{
		if (pipe(fd) == -1)
			master_clean(0, cmd_start->env, cmd_execution, 1);
		pid = fork();
		if (pid == -1)
			master_clean(0, cmd_start->env, cmd_execution, 1);
		if (pid == 0)
		{
			//Handle fd overflow before this point
			last = cmd_execution->last_in;
			if (last)
			{
				while (last)
				{
					last_input = last->file;
					if (last_input->fd_operator <= 2)
					{
						last_input->fd = open(last_input->address, O_RDONLY);
						if (last_input->fd == -1)
							master_clean(0, cmd_start->env, cmd_execution, 1);
						if (dup2(last_input->fd, last_input->fd_operator) == -1)
							master_clean(0, cmd_start->env, cmd_execution, 1);
					}
					last = last->next;
				}
			}
			last = cmd_execution->last_out;
			if (last)
			{
				while (last)
				{
					last_output = last->file;
					if (last_output->fd_operator <= 2)
					{
						if (last_output->trunc)
							last_output->fd = open(last_output->address,
									O_RDWR | O_CREAT | O_TRUNC, 0644);
						else if (last_output->append)
							last_output->fd = open(last_output->address,
									O_RDWR | O_CREAT | O_APPEND, 0644);
						if (last_output->fd == -1)
							master_clean(0, cmd_start->env, cmd_execution, 1);
						if (dup2(last_output->fd, last_output->fd_operator) == -1)
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
			else if (cmd_count(cmd_start) > cmd_execution->index)
			{
				if (dup2(fd[1], STDOUT_FILENO) == -1)
					master_clean(0, cmd_start->env, cmd_execution, 1);
			}
			close(fd[0]);
			close(fd[1]);
			env_pack = run_builtin(cmd_execution);
			if (is_builtin(cmd_execution) == -1)
			{
				execution_package(cmd_execution, &cmd_address, &cmd_args, &cmd_env);
				if (cmd_execution->error)
				{
					free(cmd_address);
					clean_2d_char(cmd_args);
					clean_2d_char(cmd_env);
					master_clean(0, cmd_start->env, cmd_start, 1);
				}
				master_clean(0, cmd_start->env, cmd_start, -1);
				if (execve(cmd_address, cmd_args, 0) == -1)
				{
					perror("bash");
					free(cmd_address);
					clean_2d_char(cmd_args);
					clean_2d_char(cmd_env);
				}
			}
		}
		else
		{
			close(fd[1]);
			if (cmd_execution->index < cmd_count(cmd_start))
				dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			if (cmd_execution->index == cmd_count(cmd_start))
			{
				waitpid(pid, &status, 0);
				if (WIFEXITED(status))
					status = WEXITSTATUS (status);
				else if (WIFSIGNALED(status))
					status = WTERMSIG(status) + 128;
				index = 1;
				while (index < cmd_execution->index)
				{
					wait(0);
					index++;
				}
			}
		}
	}
	return (env_pack);
}
