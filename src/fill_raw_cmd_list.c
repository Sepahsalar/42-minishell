/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_raw_cmd_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:35:57 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/13 18:11:27 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	fill_raw_cmd_list(t_cmd **cmd, char **raw_cmd)
{
	int		index;
	t_cmd	*temp;

	temp = *cmd;
	index = 0;
	while (raw_cmd[index])
	{
		temp->raw = ft_strdup(raw_cmd[index]);
		temp->current = ft_strdup(raw_cmd[index]);
		if (!temp->raw || !temp->current)
			return (1);
		temp = temp->next;
		index++;
	}
	return (0);
}
