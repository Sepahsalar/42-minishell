/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 21:37:12 by asohrabi          #+#    #+#             */
/*   Updated: 2024/05/06 18:59:32 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	here_doc_helper(int *fd, t_last_file *last)
{
	char	*line;
	char	*limiter;

	close(fd[0]);
	limiter = last->file->limiter;
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		// line = get_next_line(last->file->fd_operator);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, limiter, find_max(line, limiter)) == 0)
		{
			free(line);
			return ;
			// exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(line, fd[1]);
		// ft_putstr_fd(line, last->file->fd_operator);
		free(line);
	}
	close(fd[1]);
}

void	here_doc(t_last_file *last)
{
	int		fd[2];
	pid_t	pid;
	char	*limiter;

	limiter = last->file->limiter;
	limiter = ft_strjoin(limiter, "\n");
	if (!limiter)
		error(EXIT_FAILURE);
	if (pipe(fd) == -1)
		error(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		error(EXIT_FAILURE);
	if (pid == 0)
		here_doc_helper(fd, last);
	else
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			error(EXIT_FAILURE);
		close(fd[0]);
	}
}
