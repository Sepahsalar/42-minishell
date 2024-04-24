/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:44:44 by nnourine          #+#    #+#             */
/*   Updated: 2024/04/24 10:02:55 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_clean_2d_char(char **array)
{
	int		index;

	index = 0;
	while (array[index])
	{
		free(array[index]);
		index++;
	}
	free(array);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

static size_t	ft_strlen_modified(char *s)
{
	size_t	len;

	len = 0;
	if (s == 0 || *s == '\0')
		return (0);
	else
	{
		while (*s != '\0' && !ft_isspace(*s) && !ft_istoken(*s))
		{
			++s;
			++len;
		}
		return (len);
	}
}

char	*ft_strdup_modified(char *s, char *token)
{
	size_t	l;
	char	*d;

	l = ft_strlen(token);
	s = s + l;
	while (*s != '\0' && ft_isspace(*s))
		++s;
	l = ft_strlen_modified(s);
	d = malloc((l + 1) * sizeof (char));
	if (d == 0)
		return (0);
	ft_memcpy (d, s, l);
	d[l] = '\0';
	return (d);
}

char	*ft_remove(char *str, char *del1, char *del2)
{
	int		len1;
	int		len2;
	char	*part2;
	char	*temp;
	char	*result;

	len1 = ft_strnstr(str, del1, ft_strlen(str)) - str;
	part2 = ft_strnstr(str, del2, ft_strlen(str)) + ft_strlen(del2);
	temp = part2;
	len2 = 0;
	while (*temp)
	{
		len2++;
		temp++;
	}
	result = malloc((len1 + len2 + 1) * sizeof(char));
	if (!result)
		return (0);
	ft_memcpy(result, str, len1);
	ft_memcpy(result + len1, part2, len2);
	result[len1 + len2] = '\0';
	free(str);
	return (result);
}
