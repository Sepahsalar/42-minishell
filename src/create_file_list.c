/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:07:14 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/27 16:09:22 by nnourine         ###   ########.fr       */
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

t_file	*create_file_node(int	place)
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

// t_file	*create_file_list(int total_number)
// {
// 	t_file	*first;
// 	t_file	*new;
// 	t_file	*old;
// 	int		index;

// 	if (total_number <= 0)
// 		return (0);
// 	index = 0;
// 	while (index < total_number)
// 	{
// 		new = create_file_node();
// 		if (index == 0)
// 			first = new;
// 		else
// 			old->next = new;
// 		if (!new)
// 			return (clean_file_list(first));
// 		old = new;
// 		index++;
// 	}
// 	return (first);
// }
