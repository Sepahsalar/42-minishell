/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:56:47 by asohrabi          #+#    #+#             */
/*   Updated: 2024/05/29 14:57:21 by asohrabi         ###   ########.fr       */
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
	int     	status;
	t_env_pack	env_pack;
	t_cmd		*temp_cmd;

	status = 0;
	last_input = NULL;
	last_output = NULL;
	env_pack.env = cmd_execution->env;
	env_pack.original_env = cmd_execution->original_env;

	temp_file = cmd_execution->all;
	while (temp_file)
	{
		if (temp_file->input)
		{
			if (temp_file->read == 0 && !temp_file->limiter)
			{
				if (temp_file->exist == 0)
				{
					ft_putstr_fd("bash: ", 2);
					ft_putstr_fd(temp_file->address, 2);
					ft_putendl_fd(": No such file or directory", 2);
					master_clean(0, cmd_start->env, cmd_start, -1);
					env_pack.original_env
						= export_original(env_pack.original_env, 1);
					cmd_execution->file_error = 1;
					break ;
				}
				else
				{
					ft_putstr_fd("bash: ", 2);
					ft_putstr_fd(temp_file->address, 2);
					ft_putendl_fd(": Permission denied", 2);
					master_clean(0, cmd_start->env, cmd_start, -1);
					env_pack.original_env
						= export_original(env_pack.original_env, 1);
					cmd_execution->file_error = 1;
					break ;
				}
			}
		}
		else if (temp_file->trunc || temp_file->append)
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
				break ;
			}
			close(temp_file->fd);
		}
		temp_file = temp_file->next;
	}
	if (cmd_execution->cmd_name == NULL
		|| (*cmd_execution->cmd_name == '\0' && cmd_execution->empty_cmd != 1))
	{
		env_pack.original_env = export_original(env_pack.original_env, 0);
		cmd_execution->file_error = 1;
	}
	if ((!cmd_execution->exec || cmd_execution->dir)
		&& is_builtin(cmd_execution) == -1 && !cmd_execution->file_error)
	{
		if (cmd_execution->dir)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(cmd_execution->cmd_name, 2);
			ft_putendl_fd(": is a directory", 2);
			master_clean(0, cmd_start->env, cmd_execution, -1);
			env_pack.original_env = export_original(env_pack.original_env, 126);
			cmd_execution->file_error = 1;
		}
		else
		{
			if (cmd_execution->exist)
			{
				ft_putstr_fd("bash: ", 2);
				ft_putstr_fd(cmd_execution->cmd_name, 2);
				ft_putendl_fd(": Permission denied", 2);
				master_clean(0, cmd_start->env, cmd_execution, -1);
				env_pack.original_env
					= export_original(env_pack.original_env, 126);
				cmd_execution->file_error = 1;
			}
			else
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
			}
		}
	}
	if (cmd_count(cmd_start) == 1 && (is_builtin(cmd_execution) == 2
			|| is_builtin(cmd_execution) == 4 || is_builtin(cmd_execution) == 5
			|| is_builtin(cmd_execution) == 7) && !cmd_execution->file_error)
	{
		if (is_builtin(cmd_execution) == 7 || is_builtin(cmd_execution) == 4)
		{
			last = cmd_execution->last_out;
			if (last && !cmd_execution->file_error)
			{
				while (last)
				{
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
					last = last->next;
				}
			}
			env_pack = run_builtin(cmd_execution);
		}
		else
			env_pack = run_builtin(cmd_execution);
	}
	else
	{
		if (pipe(fd) == -1)
			master_clean(0, cmd_start->env, cmd_execution, 1);
		cmd_execution->pid = fork();
		if (cmd_execution->pid == -1)
			master_clean(0, cmd_start->env, cmd_execution, 1);
		if (cmd_execution->pid == 0)
		{
			last = cmd_execution->last_in;
			if (last && !cmd_execution->file_error)
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
						close(last_input->fd);
					}
					last = last->next;
				}
			}
			last = cmd_execution->last_out;
			if (last && !cmd_execution->file_error)
			{
				while (last)
				{
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
					last = last->next;
				}
				last = cmd_execution->last_out;
				while (last && last->file->fd_operator != 1)
					last = last->next;
				if (!last || last->file->fd_operator != 1)
					dup2(fd[1], STDOUT_FILENO);
			}
			else if (cmd_count(cmd_start) > cmd_execution->index
				&& !cmd_execution->file_error)
			{
				if (dup2(fd[1], STDOUT_FILENO) == -1)
					master_clean(0, cmd_start->env, cmd_execution, 1);
			}
			close(fd[0]);
			close(fd[1]);
			if (cmd_execution->file_error)
				exit(ft_atoi(env_pack.original_env->value));
			if (is_builtin(cmd_execution) != -1)
			{
				env_pack = run_builtin(cmd_execution);
				exit(ft_atoi(env_pack.original_env->value));
			}
			else if (is_builtin(cmd_execution) == -1)
			{
				execution_package(cmd_execution, &cmd_address,
					&cmd_args, &cmd_env);
				if (cmd_execution->error)
				{
					free(cmd_address);
					clean_2d_char(cmd_args);
					clean_2d_char(cmd_env);
					master_clean(0, cmd_start->env, cmd_start, 1);
					exit(1);
				}
				master_clean(0, cmd_start->env, cmd_start, -1);
				if (execve(cmd_address, cmd_args, 0) == -1)
				{
					perror("bash");
					free(cmd_address);
					clean_2d_char(cmd_args);
					clean_2d_char(cmd_env);
					exit(1);
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
				close(STDIN_FILENO);
				waitpid(cmd_execution->pid, &status, 0);
				temp_cmd = cmd_start;
				while (temp_cmd != cmd_execution)
				{
					waitpid(temp_cmd->pid, NULL, 0);
					temp_cmd = temp_cmd->next;
				}
				if (WIFEXITED(status))
					status = WEXITSTATUS (status);
				else if (WIFSIGNALED(status))
					status = WTERMSIG(status) + 128;
				env_pack.original_env
					= export_original(env_pack.original_env, status);
			}
		}
	}
	return (env_pack);
}
