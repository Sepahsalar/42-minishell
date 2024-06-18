/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:29:05 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/18 10:52:54 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	load_history(char *root)
{
	int		fd_history;
	char	*line;
	char	*temp;
	char	*address;

	address = ft_strjoin(root, "/.history");
	if (!address)
	    return (1);
	fd_history = open(address, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd_history < 0)
	    return (1);
	line = get_next_line(fd_history);
	if (line)
	{
		temp = line;
		line = ft_strtrim(line, "\n");
		if (temp)
			free(temp);
		if (!line)
		    return (1);
		while (line)
		{
			add_history(line);
			free(line);
			line = get_next_line(fd_history);
			if (line)
			{
				temp = line;
				line = ft_strtrim(line, "\n");
				if (temp)
					free(temp);
				if (!line)
				    return (1);
			}
		}
	}
	close(fd_history);
	free(address);
	return (0);
}

int	save_history(char *raw_line, char *root)
{
	int	fd_history;
	char *address;

	address = ft_strjoin(root, "/.history");
	if (!address)
	    return (1);
	fd_history = open(address, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd_history == -1)
	    return (1);
	ft_putendl_fd(raw_line, fd_history);
	close(fd_history);
	free(address);
	return (0);
}
