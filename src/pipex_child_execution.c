/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_child_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:59:53 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/19 11:37:33 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_process(t_cmd *cmd_start, t_cmd *cmd_execution,
		t_env_pack env_pack, int fd[2])
{
	if (!cmd_execution->file_error)
	{
		input_output_open(cmd_start, cmd_execution);
		input_output_redirect(cmd_start, cmd_execution, fd);
		close_all(cmd_execution);
	}
	if (close(fd[0]) == -1 || close(fd[1]) == -1)
		master_clean(NULL, cmd_start, EXIT_FAILURE);
	child_execution(cmd_start, cmd_execution, env_pack);
}

void	input_output_redirect(t_cmd *cmd_start, t_cmd *cmd_execution, int fd[2])
{
	input_redirect(cmd_start, cmd_execution);
	output_redirect(cmd_start, cmd_execution, fd);
}

void	child_execution(t_cmd *cmd_start, t_cmd *cmd_execution,
	t_env_pack env_pack)
{
	if (cmd_execution->file_error)
		exit(ft_atoi(env_pack.original_env->value));
	if (is_builtin(cmd_execution) != -1)
		builtin_child_execution(cmd_start, cmd_execution, env_pack);
	else if (is_builtin(cmd_execution) == -1)
		non_builtin_execution(cmd_start, cmd_execution);
}

void	builtin_child_execution(t_cmd *cmd_start, t_cmd *cmd_execution,
	t_env_pack env_pack)
{
	(void)cmd_start;
	cmd_execution->child_builtin = 1;
	env_pack = run_builtin(cmd_execution);
	exit(ft_atoi(env_pack.original_env->value));
}

void	non_builtin_execution(t_cmd *cmd_start, t_cmd *cmd_execution)
{
	char		*cmd_address;
	char		**cmd_args;
	char		**cmd_env;

	execution_package(cmd_execution, &cmd_address,
		&cmd_args, &cmd_env);
	if (cmd_execution->error)
	{
		free(cmd_address);
		clean_2d_char(cmd_args);
		clean_2d_char(cmd_env);
		clean_cmd_list(cmd_start);
		clean_env_list(cmd_execution->env);
		clean_env_list(cmd_execution->original_env);
		master_clean(0, cmd_start, 1);
		exit(1);
	}
	clean_cmd_list(cmd_start);
	run_execve(cmd_address, cmd_args, cmd_env);
}
