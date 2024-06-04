/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:10:21 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/04 12:30:10 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**split_pipex(const char *s)
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

char	**split_pipex_pipe(const char *s)
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
