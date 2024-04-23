/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:56:29 by asohrabi          #+#    #+#             */
/*   Updated: 2024/04/23 17:20:59 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	open_file(char *argv, int i)
{
	int	fd;

	if (i == 0)
	{
		if (access(argv, F_OK | R_OK) == -1)
			error(EXIT_SUCCESS);
		fd = open(argv, O_RDONLY);
	}
	else if (i == 1)
	{
		if (access(argv, F_OK) == 0 && access(argv, W_OK) == -1)
			error(EXIT_FAILURE);
		fd = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else
	{
		if (access(argv, F_OK) == 0 && access(argv, W_OK) == -1)
			error(EXIT_FAILURE);
		fd = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (fd == -1)
		error(EXIT_FAILURE);
	return (fd);
}
