// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   fd_heredoc.c                                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/05/08 09:59:53 by nnourine          #+#    #+#             */
// /*   Updated: 2024/05/08 14:13:05 by nnourine         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../include/minishell.h"

// int	ft_fd_heredoc(t_cmd **cmd_address)
// {
// 	t_cmd	*cmd;
// 	t_file	*temp_input;
// 	char	*file_name;
// 	char	*temp_str;
// 	char	*heredoc_text;
// 	char	*temp_heredoc_text;
// 	char 	*line;

// 	if (!cmd_address || !*cmd_address || !((*cmd_address)->input))
// 		return (0);
// 	cmd = *cmd_address;
// 	temp_input = cmd->input;
// 	file_name = 0;
// 	heredoc_text = 0;
// 	while (temp_input)
// 	{
// 		if (temp_input->limiter)
// 		{
// 			printf("limiter of this heredoc is %s\n", temp_input->limiter);
// 			if (cmd->fd_heredoc == -2)
// 			{
// 				temp_str = ft_itoa(cmd->index);
// 				if (!temp_str)
// 					return (1);
// 				file_name = ft_strjoin("temp_heredoc_", temp_str);
// 				if (!file_name)
// 				{
// 					free(temp_str);
// 					return (1);
// 				}
// 				cmd->heredoc_file = file_name;
// 				// free(temp_str);
// 				cmd->fd_heredoc = open(file_name,
// 						O_RDWR | O_CREAT | O_APPEND, 0644);
// 				// if (file_name)
// 				// 	free(file_name);
// 				if (cmd->fd_heredoc < 0)
// 				{
// 					free(file_name);
// 					return (1);
// 				}
// 			}
// 			temp_str = ft_strjoin(temp_input->limiter, "\n");
// 			if (!temp_str)
// 				return (1);
// 			ft_putstr_fd("> ", STDOUT_FILENO);
// 			printf("we are reading the first line\n");
// 			line = get_next_line(STDIN_FILENO);
// 			if (!line)
// 				return (1);
// 			printf("the first line is %s\n", line);
// 			while (ft_strlen(line) != ft_strlen(temp_str)
// 				|| ft_strncmp(line, temp_str, ft_strlen(temp_str)))
// 			{
// 				printf("we are in the loop of heredoc\n");
// 				if (!heredoc_text)
// 					heredoc_text = ft_strdup(line);
// 				else
// 				{
// 					temp_heredoc_text = heredoc_text;
// 					heredoc_text = ft_strjoin(heredoc_text, line);
// 					// printf("heredoc_text\n");
// 					if (!heredoc_text)
// 					{
// 						free(line);
// 						free(temp_heredoc_text);
// 						free(temp_str);
// 						return (1);
// 					}
// 					free(temp_heredoc_text);
// 				}
// 				printf("after heredoc text protection\n");
// 				free(line);
// 				ft_putstr_fd("> ", STDOUT_FILENO);
// 				line = get_next_line(STDIN_FILENO);
// 			}
// 			free(line);
// 			free(temp_str);
// 			ft_putstr_fd(heredoc_text, cmd->fd_heredoc);
// 			free(heredoc_text);
// 			printf("end of heredoc for the limiter of %s\n", temp_input->limiter);
// 		}
// 		temp_input = temp_input->next;
// 	}
// 	return (0);
// }

// // int	ft_fill_fd_heredoc(t_cmd *start_cmd)
// // {
// // 	t_cmd	*cmd;

// // 	if (!start_cmd)
// // 		return (0);
// // 	cmd = start_cmd;
// // 	while (cmd)
// // 	{
// // 		if (ft_fd_heredoc(&cmd))
// // 			return (1);
// // 		cmd = cmd->next;
// // 	}
// // 	return (0);
// // }


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:59:53 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/08 14:13:05 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_fd_heredoc(t_cmd **cmd_address)
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
			{
				// free(file_name);
				return (1);
			}
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

int	ft_fill_fd_heredoc(t_cmd **start_cmd)
{
	t_cmd	*cmd;

	if (!start_cmd)
		return (0);
	cmd = *start_cmd;
	while (cmd)
	{
		if (ft_fd_heredoc(&cmd))
			return (1);
		cmd = cmd->next;
	}
	return (0);
}
