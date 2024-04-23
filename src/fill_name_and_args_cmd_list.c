/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_name_and_args_cmd_list.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:34:04 by nnourine          #+#    #+#             */
/*   Updated: 2024/04/23 10:57:11 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_fill_name_and_args_cmd_list(t_cmd **cmd)
{
	t_cmd	*temp;

	temp = *cmd;
	while (temp)
	{
		temp->args = ft_create_args(temp->current);
		if (temp->args == NULL)
			return (1);
		temp->cmd_name = (temp->args)[0];
		temp = temp->next;
	}
	return (0);
}
