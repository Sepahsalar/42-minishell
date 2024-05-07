/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:04:15 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/07 12:53:43 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_all_space(char *str)
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

char	**ft_copy_2d_char(char **src)
{
	char	**dest;
	int		i;

	i = 0;
	dest = (char **)malloc(sizeof(char *) * (ft_char_2d_count(src) + 1));
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
