/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipex_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:15:02 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/18 20:53:28 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_words(const char *s, char ch)
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
		if ((s[i] != ch) && (i == 0 || (i > 0 && s[i - 1] == ch))
			&& triger1 == 0 && triger2 == 0)
			count++;
		triger1 = triger_maker(triger1, s[i], 34);
		triger2 = triger_maker(triger2, s[i], 39);
		i++;
	}
	return (count);
}

static int	len_quote_helper(const char *s, char ch)
{
	char	temp;
	int		triger_change;
	int		j;

	temp = ch;
	triger_change = 1;
	j = 0;
	while (s[j] && !((s[j] != temp)
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
	while (!triger_change && s[j] && s[j] != ch)
		j++;
	return (j);
}

int	len_quote(const char *s, char ch)
{
	int		j;

	if ((*s != 34 && *s != 39))
		j = len_quote_helper(s, ch);
	else
		j = len_helper(s);
	return (j + 1);
}

int	len_quote_pipe(const char *s, char ch)
{
	int		j;

	if ((*s != 34 && *s != 39))
	{
		j = len_quote_helper(s, ch);
		if (s[j] == ch)
			j--;
	}
	else
		j = len_helper_pipe(s);
	return (j + 1);
}
