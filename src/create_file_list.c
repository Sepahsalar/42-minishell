/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:07:14 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/06 12:56:12 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clean_file_node(t_file *node)
{
	if (node)
	{
		if (node->raw)
			free (node->raw);
		if (node->address)
			free (node->address);
		if (node->limiter)
			free (node->limiter);
		if (node->fd > 2)
			close(node->fd);
		free (node);
	}
}

t_file	*clean_file_list(t_file *first)
{
	t_file	*node;
	t_file	*temp;

	node = first;
	while (node)
	{
		temp = node->next;
		clean_file_node(node);
		node = temp;
	}
	return (0);
}

t_file	*create_file_node(int place)
{
	t_file			*new;

	new = malloc(sizeof(t_file));
	if (!new)
		return (0);
	ft_memset(new, 0, sizeof(t_file));
	new->fd = -2;
	new->place = place;
	return (new);
}
