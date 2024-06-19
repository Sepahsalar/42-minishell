/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:59:53 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/19 12:53:30 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_user_text(t_cmd *cmd, t_file *temp_input)
{
	char	*heredoc_text;
	char	*line;

	heredoc_text = NULL;
	line = readline("> ");
	while (line && !same(line, temp_input->limiter) && g_signal == HEREDOC)
	{
		if (heredoc_actions(cmd, &line, &heredoc_text))
			return (1);
		line = readline("> ");
	}
	if (line)
	    free(line);
	ft_putstr_fd(heredoc_text, temp_input->fd);
	free(heredoc_text);
	return (0);
}

int	close_heredoc_file(t_file *temp_input)
{
	if (temp_input->fd > 2)
		if (close(temp_input->fd) == -1)
			return (1);
	temp_input->fd = -2;
	return (0);
}

int	fd_heredoc(t_cmd **cmd_pointer)
{
	t_cmd	*cmd;
	t_file	*temp_input;

	if (!cmd_pointer || !*cmd_pointer || !((*cmd_pointer)->input))
		return (0);
	cmd = *cmd_pointer;
	temp_input = cmd->input;
	while (temp_input && g_signal == HEREDOC)
	{
		if (temp_input->limiter)
		{
			if (create_heredoc_file(cmd, temp_input))
				return (1);
			if (get_user_text(cmd, temp_input))
				return (1);
			if (close_heredoc_file(temp_input))
				return (1);
		}
		temp_input = temp_input->next;
	}
	return (0);
}

int	fill_fd_heredoc(t_cmd **start_cmd)
{
	t_cmd	*cmd;

	if (!start_cmd)
		return (0);
	if (change_mode(HEREDOC))
		master_clean(NULL, *start_cmd, EXIT_FAILURE);
	cmd = *start_cmd;
	while (cmd && g_signal == HEREDOC)
	{
		if (fd_heredoc(&cmd))
			return (1);
		cmd = cmd->next;
	}
	if (g_signal == HEREDOC)
		if (change_mode(RUNNING_COMMAND))
			master_clean(NULL, *start_cmd, EXIT_FAILURE);
	return (0);
}
