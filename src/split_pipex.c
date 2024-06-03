/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:10:21 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/03 18:16:29 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*dup_char(char const *s, char ch)
{
	int		len;
	char	*m;
	int		i;

	len = len_quote(s, ch);
	m = malloc ((len + 1) * sizeof(char));
	if (!m)
		return (0);
	m[len] = '\0';
	i = 0;
	while (i < len)
	{
		m[i] = s[i];
		i++;
	}
	return (m);
}

static char	*dup_char_pipe(char const *s, char ch)
{
	int		len;
	char	*m;
	int		i;

	len = len_quote_pipe(s, ch);
	m = malloc ((len + 1) * sizeof(char));
	if (!m)
		return (0);
	m[len] = '\0';
	i = 0;
	while (i < len)
	{
		m[i] = s[i];
		i++;
	}
	return (m);
}

static char	**create(char const *s, char ch, int i, int j)
{
	char	**m;
	int		triger1;
	int		triger2;

	m = malloc((count_words(s, ch) + 1) * sizeof (char *));
	if (m == 0)
		return (0);
	m[count_words(s, ch)] = 0;
	triger1 = 0;
	triger2 = 0;
	while (s[i] != '\0')
	{
		if ((i == 0 || (i > 0 && s[i - 1] == ch))
			&& s[i] != ch && triger1 == 0 && triger2 == 0)
		{
			m[j] = dup_char(s + i, ch);
			if (m[j] == 0)
				return (free_split(&m, j));
			j++;
		}
		triger1 = triger_maker_sp(triger1, s[i], 34);
		triger2 = triger_maker_sp(triger2, s[i], 39);
		i++;
	}
	return (m);
}

static char	**create_pipe(char const *s, char ch, int i, int j)
{
	char	**m;
	int		triger1;
	int		triger2;

	m = malloc((count_words(s, ch) + 1) * sizeof (char *));
	if (m == 0)
		return (0);
	m[count_words(s, ch)] = 0;
	triger1 = 0;
	triger2 = 0;
	while (s[i] != '\0')
	{
		if ((i == 0 || (i > 0 && s[i - 1] == ch))
			&& s[i] != ch && triger1 == 0 && triger2 == 0)
		{
			m[j] = dup_char_pipe(s + i, ch);
			if (m[j] == 0)
				return (free_split(&m, j));
			j++;
		}
		triger1 = triger_maker_sp(triger1, s[i], 34);
		triger2 = triger_maker_sp(triger2, s[i], 39);
		i++;
	}
	return (m);
}

char	**split_pipex(char const *s)
{
	char	**m;
	char	**temp;

	if (s == 0 || s[0] == '\0' || all_space((char *)s))
	{
		m = malloc(2 * sizeof (char *));
		if (m == 0)
			return (0);
		m[1] = 0;
		m[0] = malloc(sizeof (char));
		if (!m[0])
		{
			free(m);
			return (0);
		}
		m[0][0] = '\0';
		return (m);
	}
	m = create(s, ' ', 0, 0);
	temp = m ;
	return (m);
}

char	**split_pipex_pipe(char const *s)
{
	char	**m;
	char	**temp;

	if (s == 0 || s[0] == '\0' || all_space((char *)s))
	{
		m = malloc(2 * sizeof(char *));
		if (m == 0)
			return (0);
		m[1] = 0;
		m[0] = malloc(sizeof(char));
		if (!m[0])
		{
			free(m);
			return (0);
		}
		m[0][0] = '\0';
		return (m);
	}
	m = create_pipe(s, '|', 0, 0);
	temp = m ;
	return (m);
}
