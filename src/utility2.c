/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:04:15 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/27 15:13:33 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	char_2d_count(char **array)
{
	int		counter;

	counter = 0;
	while (array[counter])
		counter++;
	return (counter);
}

int	cmd_count(t_cmd *cmd)
{
	int	count;

	if (!cmd)
		return (0);
	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

int	all_space(char *str)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
	{
		if (!ft_isspace(str[index]))
			return (0);
		index++;
	}
	return (1);
}

char	**copy_2d_char(char **src)
{
	char	**dest;
	int		i;

	i = 0;
	dest = (char **)malloc(sizeof(char *) * (char_2d_count(src) + 1));
	if (!dest)
		return (0);
	while (src[i])
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
			return (0);
		i++;
	}
	dest[i] = 0;
	return (dest);
}

int	token_count(char *str, char *token)
{
	int		counter;
	int		index;
	char	*temp;
	char	*sq;
	char    *dq;
	int     len;

	sq = NULL;
	dq = NULL;

	if (!str || *str == '\0')
		return (0);
	if (!token || *token == '\0')
		return (0);
	counter = 0;
	index = 0;
	temp = str;
	// while (temp && *temp)
	// {
	// 	temp = ft_strnstr(temp, token, ft_strlen(temp));
	// 	if (temp)
	// 	{
	// 		temp = temp + ft_strlen(token);
	// 		counter++;
	// 	}
	// }
	index = 0;
	len = ft_strlen(str);
	while (index < len)
	{
		if (str[index] == '\"' && dq == NULL)
		{
			dq = &str[index];
			index++;
		}
		else if (str[index] == '\"')
		{
			dq = NULL;
			index++;
		}
		else if (str[index] == '\'' && sq == NULL)
		{
			sq = &str[index];
			index++;
		}
		else if (str[index] == '\'')
		{
			sq = NULL;
			index++;
		}
		else if (!sq && !dq && ft_strnstr(str + index, token, ft_strlen(token)))
		{
			// if (ft_strnstr(str + index, token, ft_strlen(token)))
			// {
				counter++;
				index = index + ft_strlen(token);
			// }
		}
		else
			index++;
	}
	return (counter);
}
