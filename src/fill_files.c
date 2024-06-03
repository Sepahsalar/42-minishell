/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:29:30 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/03 13:58:59 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	fill_files(t_cmd **cmd, char *token)
{
	t_cmd	*temp;

	temp = *cmd;
	while (temp)
	{
		if (fill_files_helper(temp->current, token, temp))
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	fill_files_all(t_cmd **cmd)
{
	t_cmd	*temp;
	t_file	*temp_file;

	temp = *cmd;
	while (temp)
	{
		if (fill_files_helper_all(temp))
			return (1);
		temp_file = temp->all;
		while (temp_file)
		{
			if (create_file_data(temp_file))
				return (1);
			temp_file = temp_file->next;
		}
		temp = temp->next;
	}
	return (0);
}
