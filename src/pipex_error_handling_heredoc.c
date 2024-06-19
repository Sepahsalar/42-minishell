/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error_handling_heredoc.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:26:41 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/19 17:35:06 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*limiter_maker_in_error(char *cur, t_env_pack env_pack)
{
	char	*limiter;
	int		limiter_len;
	char	*temp;

	temp = find_token(cur, env_pack);
	limiter_len = 0;
	while (cur[limiter_len] != ' ' && cur[limiter_len] != '\0'
		&& !temp)
	{
		limiter_len++;
		temp = find_token(cur + limiter_len, env_pack);
	}
	if (temp)
		free(temp);
	limiter = malloc(limiter_len + 2);
	if (!limiter)
		clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
	limiter[limiter_len] = '\n';
	limiter[limiter_len + 1] = '\0';
	ft_memcpy(limiter, cur, limiter_len);
	return (limiter);
}

void	handle_heredoc_error(char *token, char *cur, t_env_pack env_pack)
{
	char	*line;
	char	*limiter;

	if (same(token, "<<"))
	{
		limiter = limiter_maker_in_error(cur, env_pack);
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(0);
		while (!same(line, limiter))
		{
			free(line);
			ft_putstr_fd("> ", STDOUT_FILENO);
			line = get_next_line(0);
		}
		free(line);
		free(limiter);
	}
}

char	*change_token_heredoc(char *token, char *cur,
	int *index, t_env_pack env_pack)
{
	char	*new_token;

	new_token = find_token(cur, env_pack);
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
			handle_heredoc_error(token, cur, env_pack);
			return (NULL);
		}
		else
			return (token);
	}
}
