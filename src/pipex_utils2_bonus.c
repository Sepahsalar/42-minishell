/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:31:40 by asohrabi          #+#    #+#             */
/*   Updated: 2024/04/23 11:55:25 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

size_t	find_max(char *str1, char *str2)
{
	size_t	max;

	if (ft_strlen(str1) > ft_strlen(str2))
		max = ft_strlen(str1);
	else
		max = ft_strlen(str2);
	return (max);
}

void	error(int status)
{
	perror("Error");
	(void)status;
	// exit(status);
}

void	ft_free(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static char	*delete_backslash(char *str)
{
	char	*src;
	char	*dst;
	int		i;
	int		j;

	i = 0;
	j = 0;
	src = str;
	dst = str;
	while (src[i])
	{
		if (src[i] != '\\')
		{
			dst[j] = src[i];
			j++;
		}
		i++;
	}
	dst[j] = '\0';
	return (dst);
}

void	clean_cmd(char *str)
{
	int	i;

	i = 0;
	str = delete_backslash(str);
	while (str[i])
	{
		if (str[i] == '\t')
			str[i] = ' ';
		i++;
	}
}
