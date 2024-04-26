/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:07:14 by nnourine          #+#    #+#             */
/*   Updated: 2024/04/26 11:34:46 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	ft_clean_file_node(t_file *node)
// {
// 	if (node)
// 	{
// 		if (node->raw)
// 			free (node->raw);
// 		if (node->address)
// 			free (node->address);
// 		if (node->fd)
// 			close(node->fd);
// 		free (node);
// 	}
// }

void	ft_clean_file_node(t_file *node)
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

t_file	*ft_clean_file_list(t_file *first)
{
	t_file	*node;
	t_file	*temp;

	node = first;
	while (node)
	{
		temp = node->next;
		ft_clean_file_node(node);
		node = temp;
	}
	return (0);
}

t_file	*ft_create_file_node(void)
{
	t_file			*new;

	new = malloc(sizeof(t_file));
	if (!new)
		return (0);
	ft_memset(new, 0, sizeof(t_file));
	new->fd = -2;
	return (new);
}

t_file	*ft_create_file_list(int total_number)
{
	t_file	*first;
	t_file	*new;
	t_file	*old;
	int		index;

	if (total_number <= 0)
		return (0);
	index = 0;
	while (index < total_number)
	{
		new = ft_create_file_node();
		if (index == 0)
			first = new;
		else
			old->next = new;
		if (!new)
			return (ft_clean_file_list(first));
		old = new;
		index++;
	}
	return (first);
}
