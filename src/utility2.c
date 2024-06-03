/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:04:15 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/03 18:35:33 by asohrabi         ###   ########.fr       */
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
	if (!str || !str[0])
		return (1);
	while (str[index])
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
