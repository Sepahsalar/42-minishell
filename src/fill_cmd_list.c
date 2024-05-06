/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:43:39 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/06 18:51:44 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*ft_fill_cmd_list(char **raw_cmd, t_env *env)
{
	t_cmd	*cmd;
	int		cmd_count;

	cmd_count = ft_char_2d_count(raw_cmd);
	cmd = ft_create_cmd_list(cmd_count);
	if (!cmd)
		ft_master_clean(raw_cmd, env, 0, EXIT_FAILURE);
	ft_fill_index_cmd_list(&cmd);
	if (ft_fill_raw_cmd_list(&cmd, raw_cmd))
		ft_master_clean(raw_cmd, env, cmd, EXIT_FAILURE);
	ft_fill_env_cmd_list(&cmd, env);
	if (ft_fill_files(&cmd, ">", 1))
		ft_master_clean(raw_cmd, env, cmd, EXIT_FAILURE);
	if (ft_fill_last_out(&cmd))
		ft_master_clean(raw_cmd, env, cmd, EXIT_FAILURE);
	if (ft_fill_files(&cmd, "<", 0))
		ft_master_clean(raw_cmd, env, cmd, EXIT_FAILURE);
	if (ft_fill_last_in(&cmd))
		ft_master_clean(raw_cmd, env, cmd, EXIT_FAILURE);

	// test showing cmd names and output and the last output for each fd_operator
	t_cmd	*temp_cmd;
	t_file	*temp_file;
	t_last_file	*last;
	temp_cmd = cmd;
	while (temp_cmd)
	{
		printf("our command is %s\n", temp_cmd->raw);
		temp_file = temp_cmd->output;
		while (temp_file)
		{
			printf("one of the outputs for the above command is %s\n", temp_file->raw);
			temp_file = temp_file->next;
		}
		last = temp_cmd->last_out;
		while (last)
		{
			temp_file = last->file;
			printf("our last output for the %ld fd_operator is %s\n", temp_file->fd_operator, temp_file->raw);
			last = last->next;
		}
		temp_file = temp_cmd->input;
		while (temp_file)
		{
			printf("one of the inputs for the above command is %s\n", temp_file->raw);
			temp_file = temp_file->next;
		}
		last = temp_cmd->last_in;
		while (last)
		{
			temp_file = last->file;
			printf("our last input for the %ld fd_operator is %s\n", temp_file->fd_operator, temp_file->raw);
			last = last->next;
		}
		temp_cmd = temp_cmd->next;
	}
	
	if (ft_fill_name_and_args_cmd_list(&cmd))
		ft_master_clean(raw_cmd, env, cmd, EXIT_FAILURE);
	if (ft_fill_address_access(&cmd))
		ft_master_clean(raw_cmd, env, cmd, EXIT_FAILURE);
	if (ft_fill_file_data(&cmd))
		ft_master_clean(raw_cmd, env, cmd, EXIT_FAILURE);
	return (cmd);
}
