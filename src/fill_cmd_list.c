/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:43:39 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/28 19:01:40 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*fill_cmd_list(char **raw_cmd, t_env *env, t_env *original_env)
{
	t_cmd	*cmd;
	int		cmd_count;

	cmd_count = char_2d_count(raw_cmd);
	cmd = create_cmd_list(cmd_count);
	if (!cmd)
		master_clean(raw_cmd, env, 0, EXIT_FAILURE);
	fill_index_cmd_list(&cmd);
	if (fill_raw_cmd_list(&cmd, raw_cmd))
		master_clean(raw_cmd, env, cmd, EXIT_FAILURE);
	fill_env_cmd_list(&cmd, env);
	fill_original_env_cmd_list(&cmd, original_env);
	if (handle_dollar_struct(cmd))
		master_clean(raw_cmd, env, cmd, EXIT_FAILURE);
	if (fill_files_all(&cmd))
		master_clean(raw_cmd, env, cmd, EXIT_FAILURE);
	if (fill_files(&cmd, ">"))
		master_clean(raw_cmd, env, cmd, EXIT_FAILURE);
	if (fill_files(&cmd, "<"))
		master_clean(raw_cmd, env, cmd, EXIT_FAILURE);
	if (fill_last_out(&cmd))
		master_clean(raw_cmd, env, cmd, EXIT_FAILURE);
	// if (fill_last_out(&cmd))
	// 	master_clean(raw_cmd, env, cmd, EXIT_FAILURE);
	if (fill_last_in(&cmd))
		master_clean(raw_cmd, env, cmd, EXIT_FAILURE);
	if (fill_fd_heredoc(&cmd))
		master_clean(raw_cmd, env, cmd, EXIT_FAILURE);
	// test showing cmd names and output and the last
	// //output for each fd_operator
	// t_cmd	*temp_cmd;
	// t_file	*temp_file;
	// t_last_file	*last;
	// temp_cmd = cmd;
	// while (temp_cmd)
	// {
	// 	printf("our command is %s\n", temp_cmd->raw);
	// 	temp_file = temp_cmd->output;
	// 	while (temp_file)
	// 	{
	// 		printf("one of the outputs for the above command is %s\n",
	// 			temp_file->raw);
	// 		temp_file = temp_file->next;
	// 	}
	// 	last = temp_cmd->last_out;
	// 	while (last)
	// 	{
	// 		temp_file = last->file;
	// 		printf("our last output for the %ld fd_operator is %s\n",
	// 			temp_file->fd_operator, temp_file->raw);
	// 		last = last->next;
	// 	}
	// 	temp_file = temp_cmd->input;
	// 	while (temp_file)
	// 	{
	// 		printf("one of the inputs for the above command is %s\n",
	// 			temp_file->raw);
	// 		temp_file = temp_file->next;
	// 	}
	// 	last = temp_cmd->last_in;
	// 	while (last)
	// 	{
	// 		temp_file = last->file;
	// 		printf("our last input for the %ld fd_operator is %s\n",
	// 			temp_file->fd_operator, temp_file->raw);
	// 		last = last->next;
	// 	}
	// 	temp_cmd = temp_cmd->next;
	// }
	if (fill_args_cmd_list(&cmd))
		master_clean(raw_cmd, env, cmd, EXIT_FAILURE);
	// if (expand_all_dollar(cmd))
	// 	master_clean(raw_cmd, env, cmd, EXIT_FAILURE);
	if (handle_quote_cmd(cmd))
		master_clean(raw_cmd, env, cmd, EXIT_FAILURE);
	fill_name_cmd_list(&cmd);
	if (fill_address_access(&cmd))
		master_clean(raw_cmd, env, cmd, EXIT_FAILURE);
	if (fill_file_data(&cmd))
		master_clean(raw_cmd, env, cmd, EXIT_FAILURE);
	return (cmd);
}
