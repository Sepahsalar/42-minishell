/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_execute_actions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:39:07 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/19 14:37:48 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**create_raw_cmd(const char *input)
{
	char	**raw_cmd;

	raw_cmd = split_pipex_pipe(input);
	if (!raw_cmd)
		return (NULL);
	return (raw_cmd);
}

void	execution_package(t_cmd *cmd,
	char **cmd_address, char ***cmd_args, char ***cmd_env)
{
	if (cmd)
	{
		*cmd_address = ft_strdup(cmd->address);
		*cmd_args = copy_2d_char(cmd->args);
		*cmd_env = recreate_2d_env(cmd->env);
		if (!cmd_address ||!cmd_args ||!cmd_env)
			cmd->error = 1;
	}
}

t_env_pack	running_actions(t_cmd *cmd)
{
	t_cmd		*temp_cmd;
	t_env_pack	env_pack_result;
	int			cmd_counter;

	cmd_counter = cmd_count(cmd);
	temp_cmd = cmd;
	env_pack_result = init_env_pack(cmd);
	while (temp_cmd && g_signal == 0)
	{
		if (temp_cmd->index == cmd_counter)
			env_pack_result = execute_cmd(cmd, temp_cmd);
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
				if (unlink(temp_file->address) == -1)
					master_clean(NULL, cmd, EXIT_FAILURE);
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
	if (change_mode(RUNNING_COMMAND))
	    clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
	raw_cmd = create_raw_cmd(raw_line);
	if (!raw_cmd)
		clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
	cmd = fill_cmd_list(raw_cmd, env_pack.env, env_pack.original_env);
	env_pack_result = running_actions(cmd);
	del_herdoc_files(cmd);
	clean_cmd_list(cmd);
	return (env_pack_result);
}
