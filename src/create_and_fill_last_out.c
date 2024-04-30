/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_and_fill_last_out.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 09:20:06 by nnourine          #+#    #+#             */
/*   Updated: 2024/04/30 09:43:07 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_clean_file_nodet_last_file *node)
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
t_last_file	*ft_clean_file_listt_last_file *first)
{
t_last_file	*node;
t_last_file	*temp;

	node = first;
	while (node)
	{
		temp = node->next;
		ft_clean_file_node(node);
		node = temp;
	}
	return (0);
}
t_last_file	*ft_create_file_node(void)
{
t_last_file			*new;

	new = malloc(sizeoft_last_file);
	if (!new)
		return (0);
	ft_memset(new, 0, sizeoft_last_file);
	new->fd = -2;
	return (new);
}

int ft_unique(t_last_file	*first, t_file	*temp_out)
{
	t_last_file    *node;

    if (!first)
		return (1);
	node = first;
    while (node)
    {
        if (node->file->fd_operator == temp_out->fd)
            return (0);
        node = node->next;
    }
    return (1);
}

t_last_file	*ft_create_and_fill_last_out(t_file *output)
{
	t_last_file	*first;
	t_last_file	*new;
	t_last_file	*old;
	t_file		*temp_out;

	if (!output)
		return (0);
	temp_out = output;
	first = 0;
	while (temp_out)
	{
		if (ft_unique(first, temp_out))
		{
			new = ft_create_last_out_node();
			if (first == 0)
				first = new;
			else
				old->next = new;
			if (!new)
				return (ft_clean_last_out_list(first));
			old = new;
		}
		temp_out = temp_out->next;
	}
	return (first);
}
