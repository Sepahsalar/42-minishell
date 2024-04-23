/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_address_access_cmd_list.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:09:59 by nnourine          #+#    #+#             */
/*   Updated: 2024/04/23 14:14:01 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_fill_address_access(t_cmd **cmd)
{
	t_cmd	*temp;

	temp = *cmd;
	while (temp)
	{
		if (ft_find_cmd_address(temp))
			return (1);
		temp = temp->next;
	}
	return (0);
}
