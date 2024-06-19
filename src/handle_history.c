/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:29:05 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/19 11:35:39 by asohrabi         ###   ########.fr       */
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
	if (close(fd_history) == -1)
	    return (1);
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
	if (close(fd_history) == -1)
	    return (1);
	free(address);
	return (0);
}
