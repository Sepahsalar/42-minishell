/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:59:53 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/04 20:10:58 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	create_heredoc_file(t_cmd *cmd, t_file *temp_input)
{
	char	*file_name;
	char	*temp_str;
	char	*temp_str2;

	temp_str = ft_itoa(cmd->index);
	file_name = ft_strjoin(".temp_heredoc_", temp_str);
	free(temp_str);
	temp_str2 = ft_itoa(temp_input->fd_operator);
	temp_str = file_name;
	file_name = ft_strjoin(file_name, temp_str2);
	free(temp_str);
	free(temp_str2);
	temp_input->fd = open(file_name,
			O_RDWR | O_CREAT | O_TRUNC, 0644);
	temp_input->address = file_name;
	if (temp_input->fd < 0)
		return (1);
	return (0);
}

int	continue_heredoc(char *line, t_file *temp_input)
{
	return (line && !same(line, temp_input->limiter) && g_signal == HEREDOC);
}

int	free_heredoc(char *line, char *heredoc_text)
{
	if (line)
		free(line);
	if (heredoc_text)
		free(heredoc_text);
	return (1);
}

void	handle_hd(t_cmd *cmd, t_handle_dollar *hd_pointer);

int	handle_dollar_string(t_cmd *cmd, char **string)
{
	t_handle_dollar	hd;

	if (ft_strchr(*string, '$'))
	{
		hd.dollar = fill_dollar_list(*string);
		hd.str = *string;
		while (hd.dollar)
		{
			handle_hd(cmd, &hd);
			if (hd.str == NULL)
				return (1);
		}
		*string = hd.str;
	}
	return (0);
}

int	heredoc_actions(t_cmd *cmd, char **line, char **heredoc_text)
{
	char			*temp_str;

	if (handle_dollar_string(cmd, line))
		return (free_heredoc(*line, *heredoc_text));
	temp_str = *line;
	*line = ft_strjoin(*line, "\n");
	free(temp_str);
	if (!*line)
		return (free_heredoc(*line, *heredoc_text));
	if (!*heredoc_text)
	{
		*heredoc_text = ft_strdup(*line);
		if (!*heredoc_text)
			return (free_heredoc(*line, *heredoc_text));
	}
	else
	{
		temp_str = *heredoc_text;
		*heredoc_text = ft_strjoin(*heredoc_text, *line);
		free(temp_str);
		if (!*heredoc_text)
			return (free_heredoc(*line, *heredoc_text));
	}
	return (0);
}

int	get_user_text(t_cmd *cmd, t_file *temp_input)
{
	char	*heredoc_text;
	char	*line;

	heredoc_text = NULL;
	line = readline("> ");
	while (continue_heredoc(line, temp_input))
	{
		if (heredoc_actions(cmd, &line, &heredoc_text))
			return (1);
		line = readline("> ");
	}
	ft_putstr_fd(heredoc_text, temp_input->fd);
	return (0);
}

void	close_heredoc_file(t_file *temp_input)
{
	close(temp_input->fd);
	temp_input->fd = -2;
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
			close_heredoc_file(temp_input);
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
	change_mode(HEREDOC);
	cmd = *start_cmd;
	while (cmd && g_signal == HEREDOC)
	{
		if (fd_heredoc(&cmd))
			return (1);
		cmd = cmd->next;
	}
	if (g_signal == HEREDOC)
		change_mode(RUNNING_COMMAND);
	return (0);
}
