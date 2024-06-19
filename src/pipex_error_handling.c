/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:00:59 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/19 17:43:10 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_error_helper	check_empty_first_command(char *line, t_env_pack env_pack)
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
		if (line[e.index + 1] == '|')
		{
			e.error.not_handling = 1;
			e.error.error = "||";
		}
		else
			e.error.error = ft_strdup("|");
		if (!e.error.error)
			clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
	}
	return (e);
}

void	update_helper_error(t_error_helper *e, char *line)
{
	update_token_sq_dq(&((*e).token), &((*e).sq), &((*e).dq), line[(*e).index]);
	((*e).index)++;
}

int	should_be_replaced_with_fd(char *line, t_error error)
{
	if (!line || !error.error || error.index == 0
		|| (error.error[0] != '<' && error.error[0] != '>'))
		return (0);
	if (ft_isdigit(line[error.index - 1]))
		return (1);
	return (0);
}

char	*find_fd_of_error(char *line, t_error error)
{
	int		i;
	char	*fd;
	int		len;

	i = error.index - 1;
	while (i >= 0 && ft_isdigit(line[i]))
		i--;
	len = error.index - i - 1;
	fd = ft_substr(line, i + 1, len);
	return (fd);
}

t_error	find_error(char *line, t_env_pack env_pack)
{
	t_error_helper	e;

	e = check_empty_first_command(line, env_pack);
	if (e.error.error)
		return (e.error);
	while (e.index <= (int)ft_strlen(line))
	{
		if (line[e.index] == '\"' || line[e.index] == '\'')
			update_helper_error(&e, line);
		else
		{
			if ((e.token) && !(e.sq) && !(e.dq))
				e.error = find_error_helper(line, (e.token), e.index, env_pack);
			if (e.error.error)
			{
				if (should_be_replaced_with_fd(line, e.error))
					e.error.fd = find_fd_of_error(line, e.error);
				return (e.error);
			}
			e.token = change_token(&e, (line + e.index),
					&(e.index), env_pack);
		}
	}
	return (e.error);
}
