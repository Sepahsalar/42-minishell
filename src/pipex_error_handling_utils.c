/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error_handling_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:22:09 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/07 18:54:20 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_after_token(char *str)
{
	return (ft_strchr(str, '|') || ft_strchr(str, '<') || ft_strchr(str, '>')
		|| ((ft_strchr(str, '<') && ft_strchr(str, '<' + 1 == '<')))
		|| ((ft_strchr(str, '>') && ft_strchr(str, '>' + 1 == '>'))));
}

char	**init_token(void)
{
	char	**token;

	token = (char **)malloc(21 * sizeof(char *));
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

char	*find_token(char *cur)
{
	char	**token;
	int		index;
	char	*res;

	token = init_token();
	//protection
	index = 0;
	while (token[index])
	{
		if (ft_strncmp(cur, token[index], ft_strlen(token[index])) == 0)
		{
			res = ft_strdup(token[index]);
			free(token);
			return (res);
		}
		index++;
	}
	free(token);
	return (NULL);
}

int	accept_char(char *token, char *cur)
{
	if (same(token, "|"))
	{
		if (*cur == '|' || *cur == '\0')
			return (0);
	}
	else
	{
		if (find_token(cur) || *cur == '\0')
			return (0);
	}
	return (1);
}

char	*change_token(char *token, char *cur, int *index, int sq_dq)
{
	char	*new_token;

	if (!sq_dq)
	{
		new_token = find_token(cur);
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
