/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:21:29 by nnourine          #+#    #+#             */
/*   Updated: 2024/04/19 10:23:52 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_clean_env_node(t_env *node)
{
	if (node)
	{
		if (node->key)
			free (node->key);
		if (node->value)
			free (node->value);
		free (node);
	}
}

t_env	*ft_clean_env_list(t_env *first)
{
	t_env	*node;
	t_env	*temp;

	node = first;
	while (node)
	{
		temp = node->next;
		ft_clean_env_node(node);
		node = temp;
	}
	return (0);
}

t_env	*ft_create_env_node(void)
{
	t_env			*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	ft_memset(new, 0, sizeof(t_env));
	return (new);
}

t_env	*ft_create_env_list(int total_number)
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
		new = ft_create_env_node();
		if (index == 0)
			first = new;
		else
			old->next = new;
		if (!new)
			return (ft_clean_env_list(first));
		old = new;
		index++;
	}
	return (first);
}
