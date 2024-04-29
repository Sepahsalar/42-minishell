/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_fd_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:20:21 by nnourine          #+#    #+#             */
/*   Updated: 2024/04/29 16:05:26 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
// check test.c file
t_file	**last_output_array(t_file *start_output)
{
	t_file	*tmp;
	int		tmp_fd;
	int		fd_counter;

	if (!start_output)
		return (0);
	fd_counter = 1;
	tmp = start_output;
	while (tmp && tmp->next)
	{
		if (tmp->fd_operator != tmp->next->fd_operator)
			fd_counter++;
		tmp = tmp->next;
	}

}
