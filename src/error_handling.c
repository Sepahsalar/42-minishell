/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:00:59 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/03 14:46:27 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_error	find_error_helper(char *token, char *cur, t_error error, int index)
{
	if (same(token, "<<<") || same(token, "&&") || same(token, "\\")
		|| same(token, "||") || same(token, "*") || same(token, ";")
		|| same(token, "&") || same(token, "(") || same(token, ")")
		|| same(token, "<>") || same(token, "{") || same(token, "}")
		|| same(token, "[") || same(token, "]"))
	{
		error.not_handling = 1;
		error.error = ft_strdup(token);
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
	}
	return (error);
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
	while (line[index] && line[index] != '|')
	{
		if (line[index] != ' ')
			break ;
		index++;
	}
	if (line[index] == '|')
	{
		error.index = index;
		error.error = ft_strdup("|");
		return (error);
	}
	index = 0;
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
				return (find_error_helper(token, cur, error, index));
			token = change_token(token, cur + index, &index, (sq || dq));
		}
	}
	error.index = 0;
	error.error = NULL;
	return (error);
}
