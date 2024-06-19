/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:29:05 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/19 17:05:08 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	create_history_file(char *root)
{
	int		fd_history;
	char	*address;

	address = ft_strjoin(root, "/.history");
	if (!address)
		return (-1);
	fd_history = open(address, O_RDWR | O_CREAT | O_APPEND, 0644);
	free(address);
	if (fd_history == -1)
		return (-1);
	return (fd_history);
}

static char	*load_history_line(char *line)
{
	char	*temp;

	temp = line;
	line = ft_strtrim(line, "\n");
	free(temp);
	if (!line)
		return (NULL);
	return (line);
}

static int	load_history_file(int fd_history)
{
	char	*line;

	line = get_next_line(fd_history);
	if (line)
	{
		line = load_history_line(line);
		if (!line)
			return (1);
		while (line)
		{
			add_history(line);
			free(line);
			line = get_next_line(fd_history);
			if (line)
			{
				line = load_history_line(line);
				if (!line)
					return (1);
			}
		}
	}
	return (0);
}

int	load_history(char *root)
{
	int		fd_history;

	fd_history = create_history_file(root);
	if (fd_history == -1)
		return (1);
	if (load_history_file(fd_history))
		return (1);
	if (close(fd_history) == -1)
		return (1);
	return (0);
}

int	save_history(char *raw_line, char *root)
{
	int		fd_history;
	char	*address;

	address = ft_strjoin(root, "/.history");
	if (!address)
		return (1);
	fd_history = open(address, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd_history == -1)
		return (1);
	ft_putendl_fd(raw_line, fd_history);
	if (close(fd_history) == -1)
		return (1);
	free(address);
	return (0);
}
