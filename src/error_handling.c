/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:00:59 by asohrabi          #+#    #+#             */
/*   Updated: 2024/05/23 15:29:02 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_not_token(char *cur)
{
	char	*token[6];

	token[0] = "|";
	token[1] = "<";
	token[2] = ">";
	token[3] = "<<";
	token[4] = ">>";
	token[5] = NULL;

	while (*token)
	{
		if (same(cur, *token))
			return (0);
		(*token)++;
	}
	return (1);
}

int	accept_char(char *token, char *cur)
{
	if (same(token, "|"))
	{
		if (*cur == '|' || *cur == '\0')
			return (0);
	}
	// else if (same(token, "<") || same(token, "<<") || same(token, ">")) 
	else
	{
		if (!is_not_token(cur) || *cur == '\0')
			return (0);
	}
	return (1);
}

char *change_token(char *cur)
{
	
}
void	error_handling(char *str)
{
	
}
