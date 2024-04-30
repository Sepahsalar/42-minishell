/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_and_fill_last_out.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 09:20:06 by nnourine          #+#    #+#             */
/*   Updated: 2024/04/30 12:47:53 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_last_file	*ft_clean_last_out_list(t_last_file *first)
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

t_last_file	*ft_create_last_out_node(t_file *output, t_file *temp_out)
{
	t_last_file			*new;
	t_file				*temp_file;

	new = malloc(sizeof(t_last_file));
	if (!new)
		return (0);
	temp_file = output;
	while (temp_file)
	{
		if (temp_file->fd_operator == temp_out->fd_operator)
			new->file = temp_file;
		temp_file = temp_file->next;
	}
	new->next = 0;
	return (new);
}

int	ft_unique(t_last_file *first, t_file *temp_out)
{
	t_last_file	*node;

	if (!first)
		return (1);
	node = first;
	while (node)
	{
		if (node->file->fd_operator == temp_out->fd_operator)
			return (0);
		node = node->next;
	}
	return (1);
}

t_last_file	*ft_create_last_out_list(t_file *output)
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
			new = ft_create_last_out_node(output, temp_out);
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

int	ft_fill_last_out(t_cmd **cmd)
{
	t_cmd	*temp;

	temp = *cmd;
	while (temp)
	{
		temp->last_out = ft_create_last_out_list(temp->output);
		if (temp->output && !temp->last_out)
			return (1);
		temp = temp->next;
	}
	return (0);
}
