/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:29:05 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/05 11:29:44 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	load_history(void)
{
	int		fd_history;
	char	*line;
	char	*temp;

	fd_history = open(".history", O_RDWR | O_CREAT | O_APPEND, 0644);
	line = get_next_line(fd_history);
	if (line)
	{
		temp = line;
		line = ft_strtrim(line, "\n");
		if (temp)
			free(temp);
		while (line)
		{
			add_history(line);
			free(line);
			line = get_next_line(fd_history);
			temp = line;
			line = ft_strtrim(line, "\n");
			if (temp)
				free(temp);
		}
	}
	close(fd_history);
}

void	save_history(char *raw_line)
{
	int	fd_history;

	fd_history = open(".history", O_RDWR | O_CREAT | O_APPEND, 0644);
	ft_putendl_fd(raw_line, fd_history);
	close(fd_history);
}
