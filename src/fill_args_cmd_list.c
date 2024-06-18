/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args_cmd_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:34:04 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/18 18:12:22 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	fill_args_cmd_list(t_cmd **cmd)
{
	t_cmd	*temp;

	temp = *cmd;
	while (temp)
	{
		temp->args = split_pipex(temp->current);
		if (!temp->args)
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	fill_name_cmd_list(t_cmd **cmd)
{
	t_cmd	*temp;

	temp = *cmd;
	while (temp)
	{
		temp->cmd_name = temp->args[0];
		temp = temp->next;
	}
}
