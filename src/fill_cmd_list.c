/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:43:39 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/04 11:02:13 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	fill_cmd_list_helper(t_cmd *cmd, char **raw_cmd, t_env *env)
{
	if (handle_dollar_struct(cmd))
		master_clean(raw_cmd, env, cmd, EXIT_FAILURE);
	if (fill_files_all(&cmd))
		master_clean(raw_cmd, env, cmd, EXIT_FAILURE);
	if (fill_files(&cmd, "<"))
		master_clean(raw_cmd, env, cmd, EXIT_FAILURE);
	if (fill_files(&cmd, ">"))
		master_clean(raw_cmd, env, cmd, EXIT_FAILURE);
	if (fill_last_out(&cmd))
		master_clean(raw_cmd, env, cmd, EXIT_FAILURE);
	if (fill_last_in(&cmd))
		master_clean(raw_cmd, env, cmd, EXIT_FAILURE);
	if (fill_fd_heredoc(&cmd))
		master_clean(raw_cmd, env, cmd, EXIT_FAILURE);
	if (fill_args_cmd_list(&cmd))
		master_clean(raw_cmd, env, cmd, EXIT_FAILURE);
	if (handle_quote_cmd(cmd))
		master_clean(raw_cmd, env, cmd, EXIT_FAILURE);
}

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
	fill_cmd_list_helper(cmd, raw_cmd, env);
	fill_name_cmd_list(&cmd);
	if (fill_address_access(&cmd))
		master_clean(raw_cmd, env, cmd, EXIT_FAILURE);
	if (fill_file_data(&cmd))
		master_clean(raw_cmd, env, cmd, EXIT_FAILURE);
	return (cmd);
}
