/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_index_cmd_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:21:28 by nnourine          #+#    #+#             */
/*   Updated: 2024/04/19 09:21:40 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_fill_index_cmd_list(t_cmd **cmd)
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
