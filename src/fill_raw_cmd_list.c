/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_raw_cmd_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:35:57 by nnourine          #+#    #+#             */
/*   Updated: 2024/04/18 17:15:17 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_fill_raw_cmd_list(t_cmd **cmd, char **raw_cmd)
{
	int		index;
	t_cmd	*temp;

	temp = *cmd;
	index = 0;
	while (raw_cmd[index])
	{
		temp->raw = ft_strdup(raw_cmd[index]);
		temp->current = ft_strdup(raw_cmd[index]);
		if (!temp->raw || !temp->current)
			return (1);
		temp = temp->next;
		index++;
	}
	return (0);
}

void	ft_fill_index_cmd_list(t_cmd **cmd)
{
	int		index;
	t_cmd	*temp;

	temp = *cmd;
	index = 1;
	while (temp)
	{
		temp->index = index;
		index++;
		temp = temp->next;
	}
}

int	ft_fill_heredoc_cmd_list(t_cmd **cmd)
{
	t_cmd	*temp;
	char	*heredoc;

	temp = *cmd;
	while (temp)
	{
		heredoc = ft_strnstr(temp->raw, "<<", ft_strlen(temp->raw));
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

char	*ft_remove(char *str, char *del1, char *del2)
{
	int		len1;
	int		len2;
	char	*part2;
	char	*temp;
	char	*result;

	len1 = ft_strnstr(str, del1, ft_strlen(str)) - str;
	part2 = ft_strnstr(str, del2, ft_strlen(str)) + ft_strlen(del2);
	temp = part2;
	len2 = 0;
	while (*temp)
	{
		len2++;
		temp++;
	}
	result = malloc((len1 + len2 + 1) * sizeof(char));
	if (!result)
		return (0);
	ft_memcpy(result, str, len1);
	ft_memcpy(result + len1, part2, len2);
	result[len1 + len2] = '\0';
	free(str);
	return (result);
}
