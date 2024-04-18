/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_raw_cmd_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:35:57 by nnourine          #+#    #+#             */
/*   Updated: 2024/04/18 14:58:21 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_fill_raw_cmd_list(t_cmd **cmd, char **raw_cmd)
{
	int		index;
	t_cmd	*temp;

	temp = *cmd;
	index = 0;
	while (raw_cmd[index])
	{
		temp->raw = ft_strdup(raw_cmd[index]);
		if (!(temp->raw))
			return (1);
		temp = temp->next;
		index++;

	}
	return (0);
}
