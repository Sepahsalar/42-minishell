/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:07:14 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/19 11:32:09 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clean_cmd_node(t_cmd *node)
{
	if (node)
	{
		if (node->raw)
			free (node->raw);
		if (node->current)
			free (node->current);
		if (node->address)
			free (node->address);
		if (node->args)
			clean_2d_char(node->args);
		if (node->input)
			clean_file_list(node->input);
		if (node->output)
			clean_file_list(node->output);
		if (node->last_out)
			clean_last_file_list(node->last_out);
		if (node->last_in)
			clean_last_file_list(node->last_in);
		if (node->all)
			clean_file_list(node->all);
		if (node->std_error)
			clean_file_list(node->std_error);
		free (node);
	}
}

t_cmd	*clean_cmd_list(t_cmd *first)
{
	t_cmd	*node;
	t_cmd	*temp;

	node = first;
	while (node)
	{
		temp = node->next;
		clean_cmd_node(node);
		node = temp;
	}
	return (0);
}

t_cmd	*create_cmd_node(void)
{
	t_cmd			*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (0);
	ft_memset(new, 0, sizeof(t_cmd));
	return (new);
}

t_cmd	*create_cmd_list(int total_number)
{
	t_cmd	*first;
	t_cmd	*new;
	t_cmd	*old;
	int		index;

	if (total_number <= 0)
		return (0);
	index = 0;
	while (index < total_number)
	{
		new = create_cmd_node();
		if (index == 0)
			first = new;
		else
		{
			old->next = new;
			new->previous = old;
		}
		if (!new)
			return (clean_cmd_list(first));
		old = new;
		index++;
	}
	return (first);
}
