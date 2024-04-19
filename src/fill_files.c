/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:29:30 by nnourine          #+#    #+#             */
/*   Updated: 2024/04/19 11:51:24 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_count_files(char *current, char *token)
{
	int		count;
	char	*temp;

	count = 0;
	temp = current;
	while (temp)
	{
		temp = ft_strnstr(temp, token, ft_strlen(temp));
		if (temp)
		{
			temp = temp + ft_strlen(token) + 1;
			count++;
		}
	}
	return (count);
}


void    ft_fill_files(char *current, t_cmd **cmd)
{
	t_file	*file;

	t_cmd	*temp;
	char	*heredoc;

	temp = *cmd;
	while (temp)
	{
		heredoc = ft_strnstr(temp->current, ">>", ft_strlen(temp->current));
		if (heredoc)
		{
			temp->limiter = ft_strdup_modified(heredoc, ">>");
			if (!temp->limiter)
				return (1);
			temp->current = ft_remove(temp->current, ">>", temp->limiter);
		}
		temp = temp->next;
	}
	return (0);
}
