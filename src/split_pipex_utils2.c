/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipex_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:27:41 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/04 12:30:02 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*dup_char(const char *s, char ch)
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

char	*dup_char_pipe(const char *s, char ch)
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

char	**create(const char *s, char ch, int i, int j)
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
		triger1 = triger_maker(triger1, s[i], 34);
		triger2 = triger_maker(triger2, s[i], 39);
		i++;
	}
	return (m);
}

char	**create_pipe(const char *s, char ch, int i, int j)
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
		triger1 = triger_maker(triger1, s[i], 34);
		triger2 = triger_maker(triger2, s[i], 39);
		i++;
	}
	return (m);
}
