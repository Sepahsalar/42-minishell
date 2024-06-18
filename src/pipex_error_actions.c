/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:16:17 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/18 11:42:28 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// t_env_pack	not_handling_error(t_env_pack env_pack, t_error error)
// {
// 	t_env_pack	env_pack_result;

// 	env_pack_result = env_pack;
// 	env_pack_result.original_env
// 		= export_original(env_pack_result.original_env, 1);
// 	ft_putstr_fd("ASAL: We are not handling `", 2);
// 	ft_putstr_fd(error.error, 2);
// 	ft_putendl_fd("\'", 2);
// 	return (env_pack_result);
// }

// int	print_error_before(t_error error, char *raw_line)
// {
// 	char	*heredoc_place;

// 	heredoc_place = ft_strnstr(raw_line, "<<", error.index);
// 	if (!heredoc_place || check_after_token(raw_line + error.index
// 			+ ft_strlen(error.error) - 1))
// 	{
// 		ft_putstr_fd("bash: syntax error near unexpected token `", 2);
// 		ft_putstr_fd(error.error, 2);
// 		ft_putendl_fd("\'", 2);
// 		return (1);
// 	}
// 	return (0);
// }

// void	print_error_after(t_error error, int printed)
// {
// 	if (!printed)
// 	{
// 		ft_putstr_fd("bash: syntax error near unexpected token `", 2);
// 		ft_putstr_fd(error.error, 2);
// 		ft_putendl_fd("\'", 2);
// 	}
// }

// static int	update_sq_dq_index(char c, int *sq, int *dq, int index)
// {
// 	if (c == '\"' && (*dq) == 0)
// 		(*dq) = 1;
// 	else if (c == '\"')
// 		(*dq) = 0;
// 	else if (c == '\'' && (*sq) == 0)
// 		(*sq) = 1;
// 	else if (c == '\'')
// 		(*sq) = 0;
// 	return (index + 1);
// }

// static int	open_sq_or_dq(char **token, int index)
// {
// 	*token = NULL;
// 	return (index + 1);
// }

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
