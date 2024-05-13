/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:08:29 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/13 18:44:50 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**free_split(char ***m, int j)
{
	int	k;

	k = 0;
	while (k < j)
	{
		free((*m)[k]);
		k++;
	}
	free (*m);
	return (0);
}

int	triger_maker_sp(int triger, char c, char divider)
{
	if (c == divider)
	{
		if (triger == 0)
			triger = 1;
		else
			triger = 0;
	}
	return (triger);
}

char	**split_all_delimiter(char const *s)
{
	char	**m;

	m = malloc(2 * sizeof (char *));
	if (m == 0)
		return (0);
	m[1] = 0;
	m[0] = ft_strdup(s);
	if (!m[0])
	{
		free(m);
		return (0);
	}
	return (m);
}

int	len_helper(const char *s)
{
	int	j;

	j = 0;
	if (*s == 34)
	{
		while (s[j + 1] && ((s[j + 1] != 34)
				|| (s[j + 2] && s[j + 1] == 34 && s[j + 2] != ' ')))
			j++;
	}
	else
	{
		while (s[j + 1] && ((s[j + 1] != 39)
				|| (s[j + 2] && s[j + 1] == 39 && s[j + 2] != ' ')))
			j++;
	}
	return (j + 1);
}

int	check_unique(t_last_file *first, t_file *temp)
{
	t_last_file	*node;

	if (!first)
		return (1);
	node = first;
	while (node)
	{
		if (node->file->fd_operator == temp->fd_operator)
			return (0);
		node = node->next;
	}
	return (1);
}
