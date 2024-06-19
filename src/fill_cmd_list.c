/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:43:39 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/19 11:20:18 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	fill_args_cmd_list(t_cmd **cmd)
{
	t_cmd	*temp;

	temp = *cmd;
	while (temp)
	{
		temp->args = split_pipex(temp->current);
		if (!temp->args)
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	fill_name_cmd_list(t_cmd **cmd)
{
	t_cmd	*temp;

	temp = *cmd;
	while (temp)
	{
		temp->cmd_name = temp->args[0];
		temp = temp->next;
	}
}

static void	fill_cmd_list_helper(t_cmd *cmd)
{
	if (fill_files_all(&cmd))
		master_clean(NULL, cmd, EXIT_FAILURE);
	if (fill_files(&cmd, "<"))
		master_clean(NULL, cmd, EXIT_FAILURE);
	if (fill_files(&cmd, ">"))
		master_clean(NULL, cmd, EXIT_FAILURE);
	if (fill_last_out(&cmd))
		master_clean(NULL, cmd, EXIT_FAILURE);
	if (fill_last_in(&cmd))
		master_clean(NULL, cmd, EXIT_FAILURE);
	if (fill_fd_heredoc(&cmd))
		master_clean(NULL, cmd, EXIT_FAILURE);
	if (handle_dollar_struct(cmd))
		master_clean(NULL, cmd, EXIT_FAILURE);
	if (fill_args_cmd_list(&cmd))
		master_clean(NULL, cmd, EXIT_FAILURE);
	if (handle_quote_cmd(cmd))
		master_clean(NULL, cmd, EXIT_FAILURE);
}

t_cmd	*fill_cmd_list(char **raw_cmd, t_env *env, t_env *original_env)
{
	t_cmd	*cmd;
	int		cmd_count;

	cmd_count = char_2d_count(raw_cmd);
	cmd = create_cmd_list(cmd_count);
	if (!cmd)
		clean_all(env, original_env, NULL, NULL);
	fill_index_cmd_list(&cmd);
	if (fill_raw_cmd_list(&cmd, raw_cmd))
		master_clean(raw_cmd, cmd, EXIT_FAILURE);
	clean_2d_char(raw_cmd);
	fill_env_cmd_list(&cmd, env);
	fill_original_env_cmd_list(&cmd, original_env);
	fill_cmd_list_helper(cmd);
	fill_name_cmd_list(&cmd);
	if (fill_address_access(&cmd))
		master_clean(NULL, cmd, EXIT_FAILURE);
	if (fill_file_data(&cmd))
		master_clean(NULL, cmd, EXIT_FAILURE);
	return (cmd);
}
