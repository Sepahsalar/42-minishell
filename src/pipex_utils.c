/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:56:47 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/18 20:12:20 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env_pack	after_child(t_cmd *cmd_start, t_cmd *cmd_execution,
		t_env_pack env_pack, int fd[2])
{
	if (close(fd[1]) == -1)
		master_clean(NULL, cmd_start, EXIT_FAILURE);
	if (cmd_execution->index < cmd_count(cmd_start))
		if (dup2(fd[0], STDIN_FILENO) == -1)
			master_clean(NULL, cmd_start, EXIT_FAILURE);
	if (close(fd[0]) == -1)
		master_clean(NULL, cmd_start, EXIT_FAILURE);
	if (cmd_execution->index == cmd_count(cmd_start))
		env_pack = waiting_process(cmd_start, cmd_execution, env_pack);
	return (env_pack);
}

t_env_pack	waiting_process(t_cmd *cmd_start, t_cmd *cmd_execution,
	t_env_pack env_pack)
{
	int		status;
	t_cmd	*temp_cmd;

	status = 0;
	if (close(STDIN_FILENO) == -1)
		master_clean(NULL, cmd_start, EXIT_FAILURE);
	if (waitpid(cmd_execution->pid, &status, 0) == -1)
		master_clean(NULL, cmd_start, EXIT_FAILURE);
	temp_cmd = cmd_start;
	while (temp_cmd != cmd_execution)
	{
		if (waitpid(temp_cmd->pid, NULL, 0) == -1)
			master_clean(NULL, cmd_start, EXIT_FAILURE);
		temp_cmd = temp_cmd->next;
	}
	if (WIFEXITED(status))
		status = WEXITSTATUS (status);
	else if (WIFSIGNALED(status))
		status = WTERMSIG(status) + 128;
	env_pack.original_env
		= export_original(env_pack.original_env, status);
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

void	run_execve(char *cmd_address, char **cmd_args, char **cmd_env)
{
	if (execve(cmd_address, cmd_args, cmd_env) == -1)
	{
		clean_2d_char(cmd_args);
		clean_2d_char(cmd_env);
		if (same(strerror(errno), "Exec format error"))
		{
			if (!check_accessibility(cmd_address, 'R'))
			{
				ft_putstr_fd("bash: ", 2);
				ft_putstr_fd(cmd_address, 2);
				free(cmd_address);
				ft_putendl_fd(": Permission denied", 2);
				exit(126);
			}
			free(cmd_address);
			exit(0);
		}
		free(cmd_address);
		perror("bash");
		exit(1);
	}
}

void	close_all(t_cmd *cmd)
{
	t_file	*temp_file;

	temp_file = cmd->output;
	while (temp_file)
	{
		if (temp_file->fd > 2)
			if (close(temp_file->fd) == -1)
				master_clean(NULL, cmd, EXIT_FAILURE);
		temp_file->fd = -2;
		temp_file = temp_file->next;
	}
	temp_file = cmd->input;
	while (temp_file)
	{
		if (temp_file->fd > 2)
			if (close(temp_file->fd) == -1)
				master_clean(NULL, cmd, EXIT_FAILURE);
		temp_file->fd = -2;
		temp_file = temp_file->next;
	}
}
