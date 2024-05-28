/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:10:21 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/28 15:26:55 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;
	int	triger1;
	int	triger2;

	if (!s)
		return (0);
	count = 0;
	triger1 = 0;
	triger2 = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if ((s[i] != c) && (i == 0 || (i > 0 && s[i - 1] == c))
			&& triger1 == 0 && triger2 == 0)
			count++;
		triger1 = triger_maker_sp(triger1, s[i], 34);
		triger2 = triger_maker_sp(triger2, s[i], 39);
		i++;
	}
	return (count);
}

static int	len_quote(char const *s, char c)
{
	int		j;
	char	temp;
	int		triger_change;

	triger_change = 1;
	j = 0;
	if ((*s != 34 && *s != 39))
	{
		temp = c;
		while (!((s[j] != temp)
				&& (s[j + 1] == '\0' || s[j + 1] == temp)))
		{
			if ((s[j] == '\'') && triger_change)
			{
				temp = '\'';
				triger_change = 0;
			}
			if ((s[j] == '\"') && triger_change)
			{
				temp = '\"';
				triger_change = 0;
			}
			j++;
		}
		while (!triger_change && s[j] && s[j] != c)
			j++;
	}
	else
		j = len_helper(s);
	return (j + 1);
}

static int	len_quote_pipe(char const *s, char c)
{
	int		j;
	char	temp;
	int		triger_change;

	triger_change = 1;
	j = 0;
	if ((*s != 34 && *s != 39))
	{
		temp = c;
		while (!((s[j] != temp)
				&& (s[j + 1] == '\0' || s[j + 1] == temp)))
		{
			if ((s[j] == '\'') && triger_change)
			{
				temp = '\'';
				triger_change = 0;
			}
			if ((s[j] == '\"') && triger_change)
			{
				temp = '\"';
				triger_change = 0;
			}
			j++;
		}
		// printf("triger_change = %d\n", triger_change);
		while (!triger_change && s[j] && s[j] != c)
			j++;
		// if (s[j] == c)
		// 	j--;
	}
	else
		j = len_helper_pipe(s);
	return (j + 1);
}



static char	*dup_char(char const *s, char c)
{
	int		len;
	char	*m;
	int		i;

	len = len_quote(s, c);
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
static char	*dup_char_pipe(char const *s, char c)
{
	int		len;
	char	*m;
	int		i;

	len = len_quote_pipe(s, c);
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

static char	**create(char const *s, char c, int i, int j)
{
	char	**m;
	int		triger1;
	int		triger2;

	m = malloc((count_words(s, c) + 1) * sizeof (char *));
	if (m == 0)
		return (0);
	m[count_words(s, c)] = 0;
	triger1 = 0;
	triger2 = 0;
	while (s[i] != '\0')
	{
		if ((i == 0 || (i > 0 && s[i - 1] == c))
			&& s[i] != c && triger1 == 0 && triger2 == 0)
		{
			m[j] = dup_char(s + i, c);
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

static char	**create_pipe(char const *s, char c, int i, int j)
{
	char	**m;
	int		triger1;
	int		triger2;

	m = malloc((count_words(s, c) + 1) * sizeof (char *));
	if (m == 0)
		return (0);
	m[count_words(s, c)] = 0;
	triger1 = 0;
	triger2 = 0;
	while (s[i] != '\0')
	{
		if ((i == 0 || (i > 0 && s[i - 1] == c))
			&& s[i] != c && triger1 == 0 && triger2 == 0)
		{
			m[j] = dup_char_pipe(s + i, c);
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
