/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:16:17 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/18 20:45:19 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	fake_heredoc(t_error error, char *raw_line, t_env_pack env_pack)
{
	int		sq;
	int		dq;
	int		index;
	char	*token;

	sq = 0;
	dq = 0;
	index = 0;
	token = NULL;
	while (index <= error.index)
	{
		if (raw_line[index] == '\"' || raw_line[index] == '\'')
			index = update_sq_dq_index(raw_line[index], &sq, &dq, index);
		else
		{
			if (sq || dq)
				index = open_sq_or_dq(&token, index);
			else
				token = change_token_heredoc(token, (raw_line + index),
						&index, error, env_pack);
		}
	}
}

t_env_pack	error_actions(t_env_pack env_pack, t_error error, char *raw_line)
{
	t_env_pack	env_pack_result;
	int			printed;

	if (error.not_handling)
		return (not_handling_error(env_pack, error));
	printed = print_error_before(error, raw_line);
	fake_heredoc(error, raw_line, env_pack);
	print_error_after(error, printed);
	env_pack_result = env_pack;
	export_original(env_pack_result.original_env, 258);
	return (env_pack_result);
}
