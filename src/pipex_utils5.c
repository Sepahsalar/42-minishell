/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:56:47 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/06 18:43:33 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	should_execute_in_parent(t_cmd *cmd_start, t_cmd *cmd_execution)
{
	return ((cmd_count(cmd_start) == 1
			&& (is_builtin(cmd_execution) == 2
				|| is_builtin(cmd_execution) == 4
				|| is_builtin(cmd_execution) == 5
				|| is_builtin(cmd_execution) == 7)
			&& !cmd_execution->file_error));
}

t_env_pack	parent_execution(t_cmd *cmd_start, t_cmd *cmd_execution,
		t_env_pack env_pack)
{
	input_output_open(cmd_start, cmd_execution, env_pack);
	output_redirect_builtin(cmd_start, cmd_execution, env_pack);
	env_pack = run_builtin(cmd_execution);
	return (env_pack);
}

void	child_process(t_cmd *cmd_start, t_cmd *cmd_execution,
		t_env_pack env_pack, int fd[2])
{
	input_output_open(cmd_start, cmd_execution, env_pack);
	input_output_redirect(cmd_start, cmd_execution, env_pack, fd);
	close(fd[0]);
	close(fd[1]);
	child_execution(cmd_start, cmd_execution, env_pack);
}

t_env_pack	after_child(t_cmd *cmd_start, t_cmd *cmd_execution,
		t_env_pack env_pack, int fd[2])
{
	close(fd[1]);
	if (cmd_execution->index < cmd_count(cmd_start))
		dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	if (cmd_execution->index == cmd_count(cmd_start))
		env_pack = waiting_process(cmd_start, cmd_execution, env_pack);
	return (env_pack);
}

t_env_pack	init_and_check(t_cmd *cmd_start, t_cmd *cmd_execution)
{
	t_env_pack	env_pack;

	env_pack = init_env_pack(cmd_execution);
	env_pack = input_output_check_create(cmd_start, cmd_execution, env_pack);
	env_pack = empty_cmd_check(cmd_start, cmd_execution, env_pack);
	env_pack = full_cmd_check(cmd_start, cmd_execution, env_pack);
	return (env_pack);
}
