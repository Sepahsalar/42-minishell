/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error_actions_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:46:17 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/19 10:20:26 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env_pack	not_handling_error(t_env_pack env_pack, t_error error)
{
	t_env_pack	env_pack_result;

	env_pack_result = env_pack;
	env_pack_result.original_env
		= export_original(env_pack_result.original_env, 1);
	ft_putstr_fd("ASAL: We are not handling `", 2);
	ft_putstr_fd(error.error, 2);
	ft_putendl_fd("\'", 2);
	return (env_pack_result);
}

int	print_error_before(t_error error, char *raw_line)
{
	char	*heredoc_place;

	heredoc_place = ft_strnstr(raw_line, "<<", error.index);
	if (!heredoc_place || (ft_strlen(raw_line) >=  (error.index
			+ ft_strlen(error.error) - 1)
			&& check_after_token(raw_line + error.index + ft_strlen(error.error) - 1)))
	{
		ft_putstr_fd("bash: syntax error near unexpected token `", 2);
		if (error.fd)
		    write(2, &error.fd, 1);
		else
			ft_putstr_fd(error.error, 2);
		free(error.error);
		ft_putendl_fd("\'", 2);
		return (1);
	}
	return (0);
}

void	print_error_after(t_error error, int printed)
{
	if (!printed)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `", 2);
		if (error.fd)
		    write(2, &error.fd, 1);
		else
			ft_putstr_fd(error.error, 2);
		free(error.error);
		ft_putendl_fd("\'", 2);
	}
}

int	update_sq_dq_index(char c, int *sq, int *dq, int index)
{
	if (c == '\"' && (*dq) == 0)
		(*dq) = 1;
	else if (c == '\"')
		(*dq) = 0;
	else if (c == '\'' && (*sq) == 0)
		(*sq) = 1;
	else if (c == '\'')
		(*sq) = 0;
	return (index + 1);
}

int	open_sq_or_dq(char **token, int index)
{
	*token = NULL;
	return (index + 1);
}
