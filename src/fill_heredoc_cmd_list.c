/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_heredoc_cmd_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:16:00 by nnourine          #+#    #+#             */
/*   Updated: 2024/04/19 09:16:21 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_fill_heredoc_cmd_list(t_cmd **cmd)
{
	t_cmd	*temp;
	char	*heredoc;

	temp = *cmd;
	while (temp)
	{
		heredoc = ft_strnstr(temp->current, "<<", ft_strlen(temp->current));
		if (heredoc)
		{
			temp->limiter = ft_strdup_modified(heredoc, "<<");
			if (!temp->limiter)
				return (1);
			temp->current = ft_remove(temp->current, "<<", temp->limiter);
		}
		temp = temp->next;
	}
	return (0);
}
