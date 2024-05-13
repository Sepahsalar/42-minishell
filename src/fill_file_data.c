/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_file_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:51:07 by asohrabi          #+#    #+#             */
/*   Updated: 2024/05/13 18:01:45 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	create_file_data(t_file *file)
{

	if (!file->raw || file->limiter)
		return (0);
	else
		file->address = handle_quote_str(file->raw);
	if (!file->address)
		return (1);
	file->exist = check_accessibility (file->address, 'F');
	file->read = check_accessibility (file->address, 'R');
	file->write = check_accessibility (file->address, 'W');
	return (0);
}

int	fill_file_data(t_cmd **cmd)
{
	t_cmd	*temp_cmd;
	t_file	*temp_file;

	temp_cmd = *cmd;
	while (temp_cmd)
	{

		temp_file = temp_cmd->input;
		while (temp_file)
		{
			if (create_file_data(temp_file))
				return (1);
			temp_file = temp_file->next;
		}
		temp_file = temp_cmd->output;
		while (temp_file)
		{
			if (create_file_data(temp_file))
				return (1);
			temp_file = temp_file->next;
		}
		// temp_file = temp_cmd->output_trunc;
		// while (temp_file)
		// {
		// 	if (ft_create_file_data(temp_file))
		// 		return (1);
		// 	temp_file = temp_file->next;
		// }
		temp_cmd = temp_cmd->next;
	}
	return (0);
}
