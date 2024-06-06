/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:29:05 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/06 20:26:57 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	load_history(char *root)
{
	int		fd_history;
	char	*line;
	char	*temp;
	char *address;

	address = ft_strjoin(root, "/.history");

	fd_history = open(address, O_RDWR | O_CREAT | O_APPEND, 0644); //we have to replace the address with joining User and value_finder home
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
	free(address);
}

void	save_history(char *raw_line, char *root)
{
	int	fd_history;
	char *address;

	address = ft_strjoin(root, "/.history");

	fd_history = open(address, O_RDWR | O_CREAT | O_APPEND, 0644);
	ft_putendl_fd(raw_line, fd_history);
	close(fd_history);
	free(address);
}
