/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:02:20 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/03 19:02:21 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env_pack	execute_cmd(t_cmd *cmd_start, t_cmd *cmd_execution)
{
	int			fd[2];
	t_env_pack	env_pack;

	env_pack = init_and_check(cmd_start, cmd_execution);
	if (should_execute_in_parent(cmd_start, cmd_execution))
		env_pack = parent_execution(cmd_start, cmd_execution, env_pack);
	else
	{
		if (pipe(fd) == -1)
			master_clean(0, cmd_start->env, cmd_execution, 1);
		cmd_execution->pid = fork();
		if (cmd_execution->pid == -1)
			master_clean(0, cmd_start->env, cmd_execution, 1);
		if (cmd_execution->pid == 0)
			child_process(cmd_start, cmd_execution, env_pack, fd);
		else
			env_pack = after_child(cmd_start, cmd_execution, env_pack, fd);
	}
	return (env_pack);
}