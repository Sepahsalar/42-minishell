/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:00:59 by asohrabi          #+#    #+#             */
/*   Updated: 2024/05/30 12:05:13 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_after_token(char *str)
{
	return (ft_strchr(str, '|') || ft_strchr(str, '<') || ft_strchr(str, '>')
		|| ((ft_strchr(str, '<') && ft_strchr(str, '<' + 1 == '<')))
		|| ((ft_strchr(str, '>') && ft_strchr(str, '>' + 1 == '>'))));
}

char	*find_token(char *cur)
{
	char	*token[11];
	int		index;

	token[0] = "|";
	token[1] = "<<<";
	token[2] = "<<";
	token[3] = "<";
	token[4] = ">>";
	token[5] = ">";
	token[6] = "||";
	token[7] = "&&";
	token[8] = "&";
	token[9] = "*";
	token[10] = NULL;

	index = 0;
	while (token[index])
	{
		if (ft_strncmp(cur, token[index], ft_strlen(token[index])) == 0)
			return (token[index]);
		index++;
	}
	return (NULL);
}

int	accept_char(char *token, char *cur)
{
	if (same(token, "|"))
	{
		if (*cur == '|' || *cur == '\0')
			return (0);
	}
	else
	{
		if (find_token(cur) || *cur == '\0')
			return (0);
	}
	return (1);
}

char	*change_token(char *token, char *cur, int *index, int sq_dq)
{
	char	*new_token;

	if (!sq_dq)
	{
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
				return (NULL);
			else
				return (token);
		}
	}
	else
	{
		*index = *index + 1;
		return (NULL);
	}
}

t_error	find_error(char *line)
{
	int		index;
	char	*token;
	char	*cur;
	int		len;
	t_error	error;
	char	*sq;
	char    *dq;

	sq = NULL;
	dq = NULL;
	index = 0;
	error.not_handling = 0;
	cur = line;
	len = (int)ft_strlen(line);
	token = NULL;
	while (index <= len)
	{

		if (cur[index] == '\"' || cur[index] == '\'')
		{
			if (cur[index] == '\"' && dq == NULL)
			{
				token = NULL;
				dq = &cur[index];
			}
			else if (cur[index] == '\"')
				dq = NULL;
			else if (cur[index] == '\'' && sq == NULL)
			{
				token = NULL;
				sq = &cur[index];
			}
			else if (cur[index] == '\'')
				sq = NULL;
			index++;
		}
		else
		{
			if (token && !sq && !dq)
			{
				if (same(token, "<<<") || same(token, "&&") || same(token, "&")
					|| same(token, "||") || same(token, "*"))
				{
					error.not_handling = 1;
					error.error = ft_strdup(token);
					return (error);
				}
				else if (!accept_char(token, cur + index))
				{
					error.index = index;
					if (cur[index] == '\0')
						error.error = ft_strdup("newline");
					else
					{
						if (find_token(cur + index))
							error.error = ft_strdup(find_token(cur + index));
						else
							error.error = sliced_str(cur, index, index);
					}
					return (error);
				}
			}
			token = change_token(token, cur + index, &index,
					(sq != NULL || dq != NULL));
		}
	}
	error.index = 0;
	error.error = NULL;
	return (error);
}

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
