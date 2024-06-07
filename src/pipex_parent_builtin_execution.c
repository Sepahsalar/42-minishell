/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_builtin_execution_parent.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:55:39 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/07 14:33:23 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	//close input output files
	//full clean 
	//current master
	return (env_pack);
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

void	output_redirect_builtin_helper(t_cmd *cmd_start,
	t_cmd *cmd_execution, t_last_file *last, t_env_pack env_pack)
{
	t_file		*last_output;

	(void)env_pack;
	last_output = last->file;
	if (last_output->fd_operator <= 2)
	{
		// if (last_output->trunc)
		// 	last_output->fd = open(last_output->address,
		// 			O_WRONLY | O_TRUNC, 0644);
		// else if (last_output->append)
		// 	last_output->fd = open(last_output->address,
		// 			O_WRONLY | O_APPEND, 0644);
		// if (last_output->fd == -1)
		// 	master_clean(0, cmd_start->env, cmd_execution, 1);
		if (dup2(last_output->fd,
				last_output->fd_operator) == -1)
			master_clean(0, cmd_start->env, cmd_execution, 1);
	}
}
