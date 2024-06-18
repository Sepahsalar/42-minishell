/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error_handling_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:22:09 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/18 11:33:57 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_after_token(char *str)
{
	return (ft_strchr(str, '|') || ft_strchr(str, '<') || ft_strchr(str, '>')
		|| ((ft_strchr(str, '<') && ft_strchr(str, '<' + 1 == '<')))
		|| ((ft_strchr(str, '>') && ft_strchr(str, '>' + 1 == '>'))));
}

char	**init_token(t_env_pack env_pack)
{
	char	**token;

	token = (char **)malloc(21 * sizeof(char *));
	if (!token)
		clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
	token[0] = "||";
	token[1] = "<>";
	token[2] = "<<<";
	token[3] = "<<";
	token[4] = "<";
	token[5] = ">>";
	token[6] = ">";
	token[7] = "|";
	token[8] = "&&";
	token[9] = "&";
	token[10] = "*";
	token[11] = "\\";
	token[12] = ";";
	token[13] = "(";
	token[14] = ")";
	token[15] = "{";
	token[16] = "}";
	token[17] = "[";
	token[18] = "]";
	token[19] = ":";
	token[20] = NULL;
	return (token);
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
			res = ft_strdup(token[index]);
			if (!res)
			    clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
			free(token);
			return (res);
		}
		index++;
	}
	free(token);
	return (NULL);
}

int	accept_char(char *token, char *cur, t_env_pack env_pack)
{
	if (same(token, "|"))
	{
		if (*cur == '|' || *cur == '\0')
			return (0);
	}
	else
	{
		if (find_token(cur, env_pack) || *cur == '\0')
			return (0);
	}
	return (1);
}

char	*change_token(char *token, char *cur, int *index, int sq_dq, t_env_pack env_pack)
{
	char	*new_token;

	if (!sq_dq)
	{
		new_token = find_token(cur, env_pack);
		if (new_token)
		{
			if (token)
				free(token);
			*index = *index + ft_strlen(new_token);
			return (new_token);
		}
		else
		{
			*index = *index + 1;
			if (*cur != ' ')
			{
				if (token)
					free(token);
				return (NULL);
			}
			else
				return (token);
		}
	}
	else
	{
		if (token)
			free(token);
		*index = *index + 1;
		return (NULL);
	}
}
