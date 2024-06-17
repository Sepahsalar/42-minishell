/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_dollar_list_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:31:42 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/17 14:22:37 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_dollar	*clean_dollar_list(t_dollar *first)
{
	t_dollar	*node;
	t_dollar	*temp;

	node = first;
	while (node)
	{
		temp = node->next;
		if (node)
			free(node);
		node = temp;
	}
	return (0);
}

t_dollar	*create_dollar_node(int id, char *place, int type)
{
	t_dollar	*new;

	new = malloc(sizeof(t_dollar));
	if (!new)
		return (0);
	new->id = id;
	new->place = place;
	new->type = type;
	new->next = NULL;
	new->previous = NULL;
	return (new);
}

int	type_finder(char *sq, char *dq, int heredoc)
{
	if (heredoc)
		return (-1);
	if (!sq && !dq)
		return (3);
	else if (!sq && dq)
		return (2);
	else if (sq && !dq)
		return (1);
	else if (sq < dq)
		return (1);
	else
		return (2);
}

void	remove_previous_node(t_dollar *current)
{
	t_dollar	*previous;

	if (current)
	{
		previous = current->previous;
		if (previous)
		{
			free(previous);
			current->previous = NULL;
		}
	}
}
