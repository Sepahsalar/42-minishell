/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:29:30 by nnourine          #+#    #+#             */
/*   Updated: 2024/04/24 17:28:39 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_file	*ft_set_temp_file(t_cmd **temp, int file_count, int type)
{
	t_file		*temp_file;

	if (type == 0)
	{
		(*temp)->input = ft_create_file_list(file_count);
		temp_file = (*temp)->input;
	}
	else
	{
		(*temp)->output = ft_create_file_list(file_count);
		temp_file = (*temp)->output;
	}
	return (temp_file);
}

void	ft_update_temp(t_cmd **temp, t_file	**temp_file, char *token)
{
	char		*temp_str;

	temp_str = ft_strnstr((*temp)->current,
			token, ft_strlen((*temp)->current));
	if (*token == '>' && *(temp_str + 1) == '>')
	{
		temp_str++;
		(*temp_file)->append = 1;
	}
	else if (*token == '>')
		(*temp_file)->trunc = 1;
	(*temp_file)->raw = ft_strdup_modified(temp_str, token);
	if (*token == '>' && *(temp_str + 1) == '>')
		(*temp)->current = ft_remove((*temp)->current, ">>", (*temp_file)->raw);
	else
		(*temp)->current
			= ft_remove((*temp)->current, token, (*temp_file)->raw);
}

int	ft_files_helper(t_cmd *temp, t_file *temp_file, int file_count, char *token)
{
	int	file_index;

	file_index = 0;
	while (file_index < file_count)
	{
		ft_update_temp(&temp, &temp_file, token);
		if (!temp->current || !temp_file->raw)
			return (1);
		temp_file = temp_file->next;
		file_index++;
	}
	return (0);
}

int	ft_fill_files(t_cmd **cmd, char *token, int type)
{
	t_cmd	*temp;
	t_file	*temp_file;
	int		file_count;

	temp = *cmd;
	while (temp)
	{
		if (*token == '>')
			file_count = ft_token_count(temp->current, ">")
				- ft_token_count(temp->current, ">>");
		else
			file_count = ft_token_count(temp->current, token);
		if (file_count > 0)
		{
			temp_file = ft_set_temp_file(&temp, file_count, type);
			if (!temp_file)
				return (1);
			if (ft_files_helper(temp, temp_file, file_count, token))
				return (1);
		}
		temp = temp->next;
	}
	return (0);
}
