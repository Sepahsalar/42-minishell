/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:59:53 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/05 11:36:29 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	input_output_redirect(t_cmd *cmd_start, t_cmd *cmd_execution,
	t_env_pack env_pack, int fd[2])
{
	input_redirect(cmd_start, cmd_execution, env_pack);
	output_redirect(cmd_start, cmd_execution, env_pack, fd);
}

t_env_pack	waiting_process(t_cmd *cmd_start, t_cmd *cmd_execution,
	t_env_pack env_pack)
{
	int		status;
	t_cmd	*temp_cmd;

	status = 0;
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
	return (env_pack);
}

void	non_builtin_execution(t_cmd *cmd_start, t_cmd *cmd_execution,
	t_env_pack env_pack)
{
	char		*cmd_address;
	char		**cmd_args;
	char		**cmd_env;

	(void)env_pack;
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
	run_execve(cmd_address, cmd_args, cmd_env);
}

void	builtin_child_execution(t_cmd *cmd_start, t_cmd *cmd_execution,
	t_env_pack env_pack)
{
	(void)cmd_start;
	cmd_execution->child_builtin = 1;
	env_pack = run_builtin(cmd_execution);
	exit(ft_atoi(env_pack.original_env->value));
}

void	child_execution(t_cmd *cmd_start, t_cmd *cmd_execution,
	t_env_pack env_pack)
{
	if (cmd_execution->file_error)
		exit(ft_atoi(env_pack.original_env->value));
	if (is_builtin(cmd_execution) != -1)
		builtin_child_execution(cmd_start, cmd_execution, env_pack);
	else if (is_builtin(cmd_execution) == -1)
		non_builtin_execution(cmd_start, cmd_execution, env_pack);
}
