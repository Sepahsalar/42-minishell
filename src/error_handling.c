/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:00:59 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/05 10:47:02 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	update_token_sq_dq(char **token, int *sq, int *dq, char c)
{
	if (c == '\"' && (*dq) == 0)
	{
		(*token) = NULL;
		(*dq) = 1;
	}
	else if (c == '\"')
		(*dq) = 0;
	else if (c == '\'' && (*sq) == 0)
	{
		(*token) = NULL;
		(*sq) = 1;
	}
	else if (c == '\'')
		(*sq) = 0;
}

int	not_handling(char *token)
{
	return (same(token, "<<<") || same(token, "&&") || same(token, "\\")
		|| same(token, "||") || same(token, "*") || same(token, ";")
		|| same(token, "&") || same(token, "(") || same(token, ")")
		|| same(token, "<>") || same(token, "{") || same(token, "}")
		|| same(token, "[") || same(token, "]"));
}

t_error	init_error(void)
{
	t_error	error;

	error.index = 0;
	error.error = NULL;
	error.not_handling = 0;
	return (error);
}

t_error	find_error_helper(char *line, char *token, int index)
{
	t_error	error;

	error = init_error();
	if (not_handling(token))
	{
		error.not_handling = 1;
		error.error = ft_strdup(token);
	}
	else if (!accept_char(token, line + index))
	{
		error.index = index;
		if (line[index] == '\0')
			error.error = ft_strdup("newline");
		else
		{
			if (find_token(line + index))
				error.error = ft_strdup(find_token(line + index));
			else
				error.error = sliced_str(line, index, index);
		}
	}
	return (error);
}

t_error_helper	init_error_helper(void)
{
	t_error_helper	helper;

	helper.token = NULL;
	helper.index = 0;
	helper.sq = 0;
	helper.dq = 0;
	helper.error = init_error();
	return (helper);
}

t_error_helper	check_empty_first_command(char *line)
{
	t_error_helper	e;

	e = init_error_helper();
	while (line[e.index] && line[e.index] != '|')
	{
		if (line[e.index] != ' ')
			break ;
		(e.index)++;
	}
	if (line[e.index] == '|')
	{
		e.error.index = e.index;
		e.error.error = ft_strdup("|");
	}
	return (e);
}

void	update_helper_error(t_error_helper *e, char *line)
{
	update_token_sq_dq(&((*e).token), &((*e).sq), &((*e).dq), line[(*e).index]);
	((*e).index)++;
}

char	*change_helper_error(t_error_helper *e, char *line)
{
	return (change_token((*e).token, (line + ((*e).index)),
			&((*e).index), ((*e).sq || (*e).dq)));
}

t_error	find_error(char *line)
{
	t_error_helper	e;

	e = check_empty_first_command(line);
	if (e.error.error)
		return (e.error);
	while (e.index <= (int)ft_strlen(line))
	{
		if (line[e.index] == '\"' || line[e.index] == '\'')
			update_helper_error(&e, line);
		else
		{
			if ((e.token) && !(e.sq) && !(e.dq))
				e.error = find_error_helper(line, (e.token), e.index);
			if (e.error.error)
				return (e.error);
			e.token = change_helper_error(&e, line);
		}
	}
	return (e.error);
}
