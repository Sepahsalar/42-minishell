/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:59:53 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/29 17:34:21 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	sig_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(0, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\033[1A");
		g_signal = sig;
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		// printf (ANSI_MOVE_UP"> "ANSI_COLOR_GREEN "[ASAL]" ANSI_COLOR_RESET"$\n");
	}
}

char	*custom_get_next_line(void)
{
	char	buf[2];
	char	*line;
	char	*temp;
	// int	i;

	line = ft_strdup("");
	buf[0] = '\0';
	buf[1] = '\0';
	// i = 0;
	// while (buf[0] != '\n' && (i > 0 && same(line, "")))
	// ft_putstr_fd("> ", STDOUT_FILENO);
	while (buf[0] != '\n')
	{
		buf[0] = '\0';
		read(STDIN_FILENO, buf, 1);
		temp = line;
		line = ft_strjoin(line, buf);
		if (same(line, ""))
			return (NULL);
	}
	// printf("line read: %s\n", line);
	return (line);
}

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
	signal(SIGINT, &sig_handler_heredoc);
	signal(SIGQUIT, &sig_handler_heredoc);
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
			// line = NULL;
			if (!line)
				return (1);
			while (!same(line, temp_str) && !g_signal)
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
					{
						break ;
					}
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
				ft_putstr_fd("> ", STDOUT_FILENO);
				// if (g_)
				// line = get_next_line(STDIN_FILENO);
				line = custom_get_next_line();
				//printf("%s", line);
			}
			// if (g_signal)
			// 	write(STDOUT_FILENO, "\n", 0);
			// free(line);
			// free(temp_str);
			ft_putstr_fd(heredoc_text, temp_input->fd);
			// free(heredoc_text);
			heredoc_text = NULL;
			temp_input->fd = -2;
		}
		temp_input = temp_input->next;
	}
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, &sig_handler);
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
