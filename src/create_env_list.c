/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:21:29 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/06 17:23:44 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clean_env_node(t_env *node)
{
	if (node)
	{
		if (node->key)
			free(node->key);
		if (node->value)
			free(node->value);
		free(node);
	}
}

// t_env	*clean_env_list(t_env *first)
void	clean_env_list(t_env *first)
{
	t_env	*node;
	t_env	*temp;

	node = first;
	while (node)
	{
		temp = node->next;
		clean_env_node(node);
		node = temp;
	}
	// return (0);
}

t_env	*create_env_node(void)
{
	t_env			*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	ft_memset(new, 0, sizeof(t_env));
	return (new);
}

t_env	*create_env_list(int total_number)
{
	t_env	*first;
	t_env	*new;
	t_env	*old;
	int		index;

	if (total_number <= 0)
		return (0);
	index = 0;
	while (index < total_number)
	{
		new = create_env_node();
		if (index == 0)
			first = new;
		else
			old->next = new;
		if (!new)
		{
			clean_env_list(first);
			return (0);
		}
		old = new;
		index++;
	}
	return (first);
}
