/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:00:59 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/05 10:58:51 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
