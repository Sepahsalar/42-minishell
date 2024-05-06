/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_and_fill_last_in.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:49:37 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/06 17:55:39 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_last_file	*ft_clean_last_in_list(t_last_file *first)
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

t_last_file	*ft_create_last_in_node(t_file *input, t_file *temp_in)
{
	t_last_file			*new;
	t_file				*temp_file;

	new = malloc(sizeof(t_last_file));
	if (!new)
		return (0);
	temp_file = input;
	while (temp_file)
	{
		if (temp_file->fd_operator == temp_in->fd_operator)
			new->file = temp_file;
		temp_file = temp_file->next;
	}
	new->next = 0;
	return (new);
}

static int	ft_unique(t_last_file *first, t_file *temp_in)
{
	t_last_file	*node;

	if (!first)
		return (1);
	node = first;
	while (node)
	{
		if (node->file->fd_operator == temp_in->fd_operator)
			return (0);
		node = node->next;
	}
	return (1);
}

t_last_file	*ft_create_last_in_list(t_file *input)
{
	t_last_file	*first;
	t_last_file	*new;
	t_last_file	*old;
	t_file		*temp_in;

	if (!input)
		return (0);
	temp_in = input;
	first = 0;
	while (temp_in)
	{
		if (ft_unique(first, temp_in))
		{
			new = ft_create_last_in_node(input, temp_in);
			if (first == 0)
				first = new;
			else
				old->next = new;
			if (!new)
				return (ft_clean_last_in_list(first));
			old = new;
		}
		temp_in = temp_in->next;
	}
	return (first);
}

int	ft_fill_last_in(t_cmd **cmd)
{
	t_cmd	*temp;

	temp = *cmd;
	while (temp)
	{
		temp->last_in = ft_create_last_in_list(temp->input);
		if (temp->input && !temp->last_in)
			return (1);
		temp = temp->next;
	}
	return (0);
}
