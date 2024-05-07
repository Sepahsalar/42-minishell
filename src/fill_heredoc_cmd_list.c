/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_heredoc_cmd_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:16:00 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/07 12:51:27 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static int	ft_update_temp_heredoc(t_cmd *temp, int heredoc_count)
// {
// 	t_heredoc	*temp_heredoc;
// 	int			heredoc_index;
// 	char		*temp_str;

// 	heredoc_index = 0;
// 	temp_heredoc = temp->limiter;
// 	while (heredoc_index < heredoc_count)
// 	{
// 		temp_str = ft_strnstr(temp->current,
// 				"<<", ft_strlen(temp->current));
// 		temp_heredoc->str = ft_strdup_modified(temp_str, "<<");
// 		if (!temp_heredoc->str)
// 			return (1);
// 		temp->current = ft_remove(temp->current,
// 				"<<", temp_heredoc->str);
// 		if (!temp->current)
// 			return (1);
// 		temp_heredoc = temp_heredoc->next;
// 		heredoc_index++;
// 	}
// 	return (0);
// }

// int	ft_fill_heredoc_cmd_list(t_cmd **cmd)
// {
// 	t_cmd	*temp;
// 	int		heredoc_count;

// 	temp = *cmd;
// 	while (temp)
// 	{
// 		heredoc_count = ft_token_count(temp->current, "<<");
// 		if (heredoc_count > 0)
// 		{
// 			temp->limiter = ft_create_heredoc_list(heredoc_count);
// 			if (!temp->limiter || ft_update_temp_heredoc(temp, heredoc_count))
// 				return (1);
// 		}
// 		temp = temp->next;
// 	}
// 	return (0);
// }
