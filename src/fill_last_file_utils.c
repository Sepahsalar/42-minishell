/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_last_file_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:46:36 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/07 11:00:48 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_last_file	*clean_last_file_list(t_last_file *first)
{
	t_last_file	*node;
	t_last_file	*temp;

	node = first;
	while (node)
	{
		temp = node->next;
		free (node);
		node = temp;
	}
	return (0);
}

t_last_file	*create_last_file_node(t_file *file, t_file *temp)
{
	t_last_file	*new;
	t_file		*temp_file;

	new = malloc(sizeof(t_last_file));
	if (!new)
		return (0);
	temp_file = file;
	while (temp_file)
	{
		if (temp_file->fd_operator == temp->fd_operator)
			new->file = temp_file;
		temp_file = temp_file->next;
	}
	new->next = 0;
	return (new);
}

t_last_file	*create_last_file_list(t_file *file)
{
	t_last_file	*first;
	t_last_file	*new;
	t_last_file	*old;
	t_file		*temp;

	if (!file)
		return (0);
	temp = file;
	first = 0;
	while (temp)
	{
		if (check_unique(first, temp))
		{
			new = create_last_file_node(file, temp);
			if (first == 0)
				first = new;
			else
				old->next = new;
			if (!new)
				return (clean_last_file_list(first));
			old = new;
		}
		temp = temp->next;
	}
	return (first);
}
