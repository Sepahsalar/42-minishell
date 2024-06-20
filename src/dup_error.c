/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:27:18 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/20 12:43:39 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	dup_error(t_cmd *cmd)
{
	t_last_file	*out;

	out = cmd->last_out;
	while (out)
	{
		if (out->file->fd_operator == 2)
		{
			if (out->file->trunc)
				out->file->fd = open(out->file->address,
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (out->file->append)
				out->file->fd = open(out->file->address,
						O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (out->file->fd != -1)
			{
				if (dup2(out->file->fd, out->file->fd_operator) == -1)
					master_clean(NULL, cmd, EXIT_FAILURE);
				if (close(out->file->fd) == -1)
					master_clean(NULL, cmd, EXIT_FAILURE);
				out->file->fd = -2;
			}
			return ;
		}
		out = out->next;
	}
}
