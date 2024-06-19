/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error_handling_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:22:09 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/19 17:03:46 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_after_token(char *str)
{
	if (!str)
		return (0);
	if (str && !str[0])
		return (0);
	return (ft_strchr(str, '|') || ft_strchr(str, '<') || ft_strchr(str, '>')
		|| ((ft_strchr(str, '<') && *(ft_strchr(str, '<') + 1) == '<'))
		|| ((ft_strchr(str, '>') && *(ft_strchr(str, '>') + 1) == '>')));
}

char	*find_token(char *cur, t_env_pack env_pack)
{
	char	**token;
	int		index;
	char	*res;

	token = init_token(env_pack);
	index = 0;
	while (token[index])
	{
		if (ft_strncmp(cur, token[index], ft_strlen(token[index])) == 0)
		{
			res = token[index];
			free(token);
			if (!res)
				clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
			return (res);
		}
		index++;
	}
	free(token);
	return (NULL);
}

int	accept_char(char *token, char *cur, t_env_pack env_pack)
{
	char	*temp;

	temp = NULL;
	if (same(token, "|"))
	{
		if (*cur == '|' || *cur == '\0')
			return (0);
	}
	else
	{
		temp = find_token(cur, env_pack);
		if (temp || *cur == '\0')
			return (0);
	}
	return (1);
}

int	is_fd_operator(char *str)
{
	int	index;

	if (!ft_isdigit(*str))
		return (0);
	index = 1;
	while (str[index] && ft_isdigit(str[index]))
		index++;
	if (str[index] == '>' || str[index] == '<')
		return (1);
	return (0);
}

char	*change_token(t_error_helper *e, char *cur,
	int *index, t_env_pack env_pack)
{
	char	*new_token;

	if (!((e->sq || e->dq)))
	{
		new_token = find_token(cur, env_pack);
		if (new_token)
		{
			*index = *index + ft_strlen(new_token);
			return (new_token);
		}
		else
		{
			*index = *index + 1;
			if (*cur != ' ' && !is_fd_operator(cur))
				return (NULL);
			else
				return (e->token);
		}
	}
	else
	{
		*index = *index + 1;
		return (NULL);
	}
}
