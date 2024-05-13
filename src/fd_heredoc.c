/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:59:53 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/13 18:08:05 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	fd_heredoc(t_cmd **cmd_address)
{
	t_cmd	*cmd;
	t_file	*temp_input;
	char	*file_name;
	char	*temp_str;
	char	*temp_str2;
	char	*heredoc_text;
	char	*temp_heredoc_text;
	char 	*line;

	if (!cmd_address || !*cmd_address || !((*cmd_address)->input))
		return (0);
	cmd = *cmd_address;
	temp_input = cmd->input;
	file_name = 0;
	heredoc_text = 0;
	while (temp_input)
	{
		//protection needed
		if (temp_input->limiter)
		{
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
			temp_str = ft_strjoin(temp_input->limiter, "\n");
			if (!temp_str)
				return (1);
			ft_putstr_fd("> ", STDOUT_FILENO);
			line = get_next_line(STDIN_FILENO);
			if (!line)
				return (1);
			while (ft_strlen(line) != ft_strlen(temp_str)
				|| ft_strncmp(line, temp_str, ft_strlen(temp_str)))
			{
				if (!heredoc_text)
					heredoc_text = ft_strdup(line);
				else
				{
					temp_heredoc_text = heredoc_text;
					heredoc_text = ft_strjoin(heredoc_text, line);
					if (!heredoc_text)
					{
						free(line);
						free(temp_heredoc_text);
						free(temp_str);
						return (1);
					}
					free(temp_heredoc_text);
				}
				free(line);
				ft_putstr_fd("> ", STDOUT_FILENO);
				line = get_next_line(STDIN_FILENO);
			}
			free(line);
			free(temp_str);
			ft_putstr_fd(heredoc_text, temp_input->fd);
			free(heredoc_text);
			heredoc_text = NULL;
			temp_input->fd = -2;
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
	cmd = *start_cmd;
	while (cmd)
	{
		if (fd_heredoc(&cmd))
			return (1);
		cmd = cmd->next;
	}
	return (0);
}
