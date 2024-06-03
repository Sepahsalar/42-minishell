/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:16:17 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/03 10:23:34 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env_pack	error_actions(t_env_pack env_pack, t_error error, char *raw_line)
{
	t_env_pack	env_pack_result;
	int			index;
	char        *token;
	char		*heredoc_place;
	int			printed = 0;
	char		*sq;
	char    	*dq;

	sq = NULL;
	dq = NULL;
	env_pack_result = env_pack;
	if (error.not_handling)
	{
		env_pack_result.original_env
			= export_original(env_pack_result.original_env, 1);
		ft_putstr_fd("ASAL: We are not handling `", 2);
		ft_putstr_fd(error.error, 2);
		ft_putendl_fd("\'", 2);
		return (env_pack_result);
	}
	export_original(env_pack_result.original_env, 258);
	index = 0;
	token = NULL;
	heredoc_place = ft_strnstr(raw_line, "<<", error.index);
	if (!heredoc_place || check_after_token(raw_line + error.index
			+ ft_strlen(error.error) - 1))
	{
		printed = 1;
		ft_putstr_fd("bash: syntax error near unexpected token `", 2);
		ft_putstr_fd(error.error, 2);
		ft_putendl_fd("\'", 2);
	}
	while (index <= error.index)
	{
		if (raw_line[index] == '\"' || raw_line[index] == '\'')
		{
			if (raw_line[index] == '\"' && dq == NULL)
				dq = &raw_line[index];
			else if (raw_line[index] == '\"')
				dq = NULL;
			else if (raw_line[index] == '\'' && sq == NULL)
				sq = &raw_line[index];
			else if (raw_line[index] == '\'')
				sq = NULL;
			index++;
		}
		else
		{
			if (sq || dq)
			{
				token = NULL;
				index++;
			}
			else
				token = change_token_heredoc(token, (raw_line + index),
						&index, error);
		}
	}
	if (!printed)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `", 2);
		ft_putstr_fd(error.error, 2);
		ft_putendl_fd("\'", 2);
	}
	return (env_pack_result);
}
