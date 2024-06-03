/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:59:53 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/03 13:57:42 by asohrabi         ###   ########.fr       */
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
	char	*temp_str3;
	char	*heredoc_text;
	char	*temp_heredoc_text;
	char 	*line;

	if (!cmd_address || !*cmd_address || !((*cmd_address)->input))
		return (0);
	cmd = *cmd_address;
	temp_input = cmd->input;
	file_name = 0;
	heredoc_text = 0;
	while (temp_input && g_signal == HEREDOC)
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
			temp_str3 = readline("> ");
			line = ft_strjoin(temp_str3, "\n");
			while (!same(line, temp_str) && line && g_signal == HEREDOC)
			{
				if (!heredoc_text)
				{
					heredoc_text = ft_strdup(line);
				}
				else
				{
					temp_heredoc_text = heredoc_text;
					if (line)
						heredoc_text = ft_strjoin(heredoc_text, line);
					else
						break ;
					if (!heredoc_text)
					{
						// free(line);
						// free(temp_heredoc_text);
						// free(temp_str);
						return (1);
					}
					free(temp_heredoc_text);
				}
				//free(line);
				temp_str3 = readline("> ");
				line = ft_strjoin(temp_str3, "\n");
			}
			ft_putstr_fd(heredoc_text, temp_input->fd);
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
