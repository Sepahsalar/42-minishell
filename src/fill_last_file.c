/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_last_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:49:37 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/27 17:25:32 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	fill_last_in(t_cmd **cmd)
{
	t_cmd	*temp;

	temp = *cmd;
	while (temp)
	{
		temp->last_in = create_last_file_list(temp->input);
		if (temp->input && !temp->last_in)
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	fill_last_out(t_cmd **cmd)
{
	t_cmd	*temp;

	temp = *cmd;
	while (temp)
	{
		temp->last_out = create_last_file_list(temp->output);
		if (temp->output && !temp->last_out)
			return (1);
		temp = temp->next;
	}
	return (0);
}
