/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:44:44 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/03 18:23:39 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clean_2d_char(char **array)
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

int	ft_isspace(int ch)
{
	if (ch == ' ' || ch == '\t' || ch == '\n'
		|| ch == '\v' || ch == '\f' || ch == '\r')
		return (1);
	return (0);
}

static size_t	strlen_modified(char *s)
{
	size_t	len;
	int		sq;
	int		dq;
	int		index;

	len = 0;
	sq = 0;
	dq = 0;
	index = 0;
	if (s == 0 || *s == '\0')
		return (0);
	sq = 0;
	dq = 0;
	while (s[index])
	{
		if (s[index] == '\"' || s[index] == '\'')
		{
			if (s[index] == '\'' && sq)
				sq = 0;
			else if (s[index] == '\'')
				sq = 1;
			else if (s[index] == '\"' && dq)
				dq = 0;
			else if (s[index] == '\"')
				dq = 1;
			len++;
		}
		else
		{
			if ((s[index] == ' ' || istoken(s[index])) && (!sq && !dq))
				break ;
			len++;
		}
		index++;
	}
	return (len);
}

char	*strdup_modified(char *s, char *token)
{
	size_t	l;
	char	*d;

	l = ft_strlen(token);
	s = s + l;
	while (*s != '\0' && ft_isspace(*s))
		++s;
	l = strlen_modified(s);
	d = malloc((l + 1) * sizeof (char));
	if (d == 0)
		return (0);
	ft_memcpy (d, s, l);
	d[l] = '\0';
	return (d);
}
