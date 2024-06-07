/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_heredoc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:26:41 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/03 14:27:07 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_heredoc_error(char *token, char *cur, t_error error)
{
	int		limiter_len;
	char	*line;
	char	*limiter;

	if (same(token, "<<"))
	{
		limiter_len = 0;
		while (cur[limiter_len] != ' ' && cur[limiter_len] != '\0'
			&& !find_token(cur + limiter_len))
			limiter_len++;
		limiter = malloc(limiter_len + 2);
		limiter[limiter_len] = '\n';
		limiter[limiter_len + 1] = '\0';
		ft_memcpy(limiter, cur, limiter_len);
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(0);
		while (!same(line, limiter))
		{
			free(line);
			ft_putstr_fd("> ", STDOUT_FILENO);
			line = get_next_line(0);
		}
		free(line);
		(void)error;
	}
}

char	*change_token_heredoc(char *token, char *cur, int *index, t_error error)
{
	char	*new_token;

	new_token = find_token(cur);
	if (new_token)
	{
		*index = *index + ft_strlen(new_token);
		return (new_token);
	}
	else
	{
		*index = *index + 1;
		if (*cur != ' ')
		{
			handle_heredoc_error(token, cur, error);
			return (NULL);
		}
		else
			return (token);
	}
}
