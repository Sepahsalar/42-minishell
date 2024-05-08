// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   create_heredoc_list.c                              :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/05/08 13:23:03 by nnourine          #+#    #+#             */
// /*   Updated: 2024/05/08 14:06:12 by nnourine         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../include/minishell.h"

// t_heredoc	*ft_clean_heredoc_list(t_heredoc *first)
// {
// 	t_heredoc	*node;
// 	t_heredoc	*temp;

// 	node = first;
// 	while (node)
// 	{
// 		temp = node->next;
// 		free (node);
// 		node = temp;
// 	}
// 	return (0);
// }

// t_heredoc	*ft_create_heredoc_node(t_file *input, t_file *temp_in)
// {
// 	t_heredoc			*new;
// 	t_file				*temp_file;

// 	new = malloc(sizeof(t_heredoc));
// 	if (!new)
// 		return (0);
// 	//ft_memset(new, 0, sizeof(t_heredoc));
// 	temp_file = input;
// 	while (temp_file)
// 	{
// 		if (temp_file->fd_operator == temp_in->fd_operator)
// 			new->file = temp_file;
// 		temp_file = temp_file->next;
// 	}
// 	new->next = 0
// 	new->fd_operator = fd_operator;
// 	new->fd_heredoc = -2;
// 	return (new);
// }

// static int	ft_unique_heredoc(t_heredoc *first, t_file *temp_in)
// {
// 	t_heredoc	*node;

// 	if (!temp_in || !(temp_in->limiter))
// 		return (0);
// 	if (!first)
// 		return (1);
// 	node = first;
// 	while (node)
// 	{
// 		if (node->fd_operator == temp_in->fd_operator)
// 			return (0);
// 		node = node->next;
// 	}
// 	return (1);
// }

// t_heredoc	*ft_create_heredoc_list(t_file *input)
// {
// 	t_heredoc	*first;
// 	t_heredoc	*new;
// 	t_heredoc	*old;
// 	t_file		*temp_in;

// 	if (!input)
// 		return (0);
// 	temp_in = input;
// 	first = 0;
// 	while (temp_in)
// 	{
// 		if (ft_unique_heredoc(first, temp_in))
// 		{
// 			new = ft_create_heredoc_node(input, temp_in);
// 			if (first == 0)
// 				first = new;
// 			else
// 				old->next = new;
// 			if (!new)
// 				return (ft_clean_heredoc_list(first));
// 			old = new;
// 		}
// 		temp_in = temp_in->next;
// 	}
// 	return (first);
// }
