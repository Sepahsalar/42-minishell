/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creatw_heredoc_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:09:10 by nnourine          #+#    #+#             */
/*   Updated: 2024/04/22 09:09:11 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_clean_heredoc_node(t_heredoc *node)
{
	if (node)
	{
		if (node->str)
			free (node->str);
		free (node);
	}
}

t_heredoc	*ft_clean_heredoc_list(t_heredoc *first)
{
	t_heredoc	*node;
	t_heredoc	*temp;

	node = first;
	while (node)
	{
		temp = node->next;
		ft_clean_heredoc_node(node);
		node = temp;
	}
	return (0);
}

t_heredoc	*ft_create_heredoc_node(void)
{
	t_heredoc			*new;

	new = malloc(sizeof(t_heredoc));
	if (!new)
		return (0);
	ft_memset(new, 0, sizeof(t_heredoc));
	return (new);
}

t_heredoc	*ft_create_heredoc_list(int total_number)
{
	t_heredoc	*first;
	t_heredoc	*new;
	t_heredoc	*old;
	int			index;

	if (total_number <= 0)
		return (0);
	index = 0;
	while (index < total_number)
	{
		new = ft_create_heredoc_node();
		if (index == 0)
			first = new;
		else
			old->next = new;
		if (!new)
			return (ft_clean_heredoc_list(first));
		old = new;
		index++;
	}
	return (first);
}
