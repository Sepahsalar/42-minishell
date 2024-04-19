/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_heredoc_cmd_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:16:00 by nnourine          #+#    #+#             */
/*   Updated: 2024/04/19 13:17:33 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// it has segfault for nodes

int	ft_fill_heredoc_cmd_list(t_cmd **cmd)
{
	t_cmd	*temp;
	char	*heredoc;
	char	*temp_heredoc;

	temp = *cmd;
	while (temp)
	{
		heredoc = ft_strnstr(temp->current, "<<", ft_strlen(temp->current));
		while (heredoc)
		{
			temp->limiter = malloc(sizeof(t_heredoc));
			if (!temp->limiter)
				return (1);
			temp->limiter->str = ft_strdup_modified(heredoc, "<<");
			// printf("str = %s\n", temp->limiter->str);
			temp_heredoc = heredoc;
			if (!temp->limiter->str)
				return (1);
			else
			{
				if (ft_strnstr(temp->limiter->str, "<<",
						ft_strlen(temp->limiter->str)))
				{
					temp_heredoc = temp->limiter->str;
					temp->limiter = temp->limiter->next;
					temp->limiter->str = ft_strdup_modified(temp_heredoc, "<<");
					// printf("str = %s\n", temp->limiter->str);
					if (!temp->limiter->str)
						return (1); // or break, so that we don't need to continue, maybe we hould handle the return better
					// continue ;
				}
			}
			temp->current = ft_remove(temp->current, "<<", temp->limiter->str);
		}
		temp = temp->next;
	}
	return (0);
}
