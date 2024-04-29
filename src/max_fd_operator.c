/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_fd_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:20:21 by nnourine          #+#    #+#             */
/*   Updated: 2024/04/29 15:33:30 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_file **last_output_array(t_file *start_output)
{
	t_file *tmp;
	int		tmp_fd;
	int fd_counter;
	if (!start_output)
	    return (NULL);
	fd_counter = 1;
	tmp = start_output;
	while (tmp)
	{
		if (tmp->)
	}
	
}