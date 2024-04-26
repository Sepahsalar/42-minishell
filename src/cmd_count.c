/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:29:49 by nnourine          #+#    #+#             */
/*   Updated: 2024/04/26 16:31:23 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_cmd_count(t_cmd *cmd)
{
	int count;

	if (!cmd)
	    return (0);
	count = 0;
	while (cmd)
	{
		count++;
        cmd = cmd->next;
	}
	return (count);
}
