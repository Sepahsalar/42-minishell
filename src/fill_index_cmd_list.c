/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_index_cmd_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:21:28 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/13 18:11:18 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	fill_index_cmd_list(t_cmd **cmd)
{
	int		index;
	t_cmd	*temp;

	temp = *cmd;
	index = 1;
	while (temp)
	{
		temp->index = index;
		index++;
		temp = temp->next;
	}
}
