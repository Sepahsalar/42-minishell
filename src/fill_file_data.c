/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_file_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:27:18 by asohrabi          #+#    #+#             */
/*   Updated: 2024/04/24 17:27:36 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_create_file_data(t_file *file)
{

	if (!file->raw)
		file->address = NULL;
	else
		file->address = ft_handle_quote_str(file->raw);
	if (!file->address)
		return (1);
	file->exist = ft_accessibility (file->address, 'F');
	file->read = ft_accessibility (file->address, 'R');
	file->write = ft_accessibility (file->address, 'W');
	return (0);
}

int	ft_fill_file_data(t_cmd **cmd)
{
	t_cmd	*temp_cmd;
	t_file	*temp_file;

	temp_cmd = *cmd;
	while (temp_cmd)
	{

		temp_file = temp_cmd->input;
		while (temp_file)
		{
			if (ft_create_file_data(temp_file))
				return (1);
			temp_file = temp_file->next;
		}
		temp_file = temp_cmd->output;
		while (temp_file)
		{
			if (ft_create_file_data(temp_file))
				return (1);
			temp_file = temp_file->next;
		}
		temp_cmd = temp_cmd->next;
	}
	return (0);
}
