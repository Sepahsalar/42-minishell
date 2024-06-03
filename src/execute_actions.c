/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:39:07 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/03 11:12:32 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env_pack	running_actions(t_cmd *cmd)
{
	t_cmd		*temp_cmd;
	t_env_pack	env_pack_result;
	int			cmd_counter;

	cmd_counter = cmd_count(cmd);
	temp_cmd = cmd;
	while (temp_cmd)
	{
		if (temp_cmd->index == cmd_counter)
		{
			env_pack_result = execute_cmd(cmd, temp_cmd);
		}
		else
			execute_cmd(cmd, temp_cmd);
		temp_cmd = temp_cmd->next;
	}
	return (env_pack_result);
}

void	del_herdoc_files(t_cmd *cmd)
{
	t_file		*temp_file;
	t_cmd		*temp_cmd;

	temp_cmd = cmd;
	while (temp_cmd)
	{
		if (temp_cmd->last_in)
			temp_file = temp_cmd->last_in->file;
		else
			temp_file = NULL;
		while (temp_file)
		{
			if (temp_file->limiter)
			{
				close(temp_file->fd); //maybe double close
				unlink(temp_file->address);
			}
			temp_file = temp_file->next;
		}
		temp_cmd = temp_cmd->next;
	}
}

t_env_pack	execute_actions(char *raw_line, t_env_pack env_pack)
{
	char		**raw_cmd;
	t_cmd		*cmd;
	t_env_pack	env_pack_result;

	env_pack_result = env_pack;
	change_mode(RUNNING_COMMAND);
	raw_cmd = create_raw_cmd(raw_line);
	cmd = fill_cmd_list(raw_cmd, env_pack.env, env_pack.original_env);
	master_clean(raw_cmd, 0, 0, -1);
	env_pack_result = running_actions(cmd);
	del_herdoc_files(cmd);
	return (env_pack_result);
}
