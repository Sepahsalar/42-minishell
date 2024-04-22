/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:29:47 by nnourine          #+#    #+#             */
/*   Updated: 2024/04/22 16:03:02 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_token_count(char *str, char *token)
{
	int		counter;
	int		index;
	char	*temp;

	if (!str || *str == '\0')
		return (0);
	if (!token || *token == '\0')
		return (0);
	counter = 0;
	index = 0;
	temp = str;
	while (temp && *temp)
	{
		temp = ft_strnstr(temp, token, ft_strlen(temp));
		if (temp)
		{
			temp = temp + ft_strlen(token);
			counter++;
		}
	}
	return (counter);
}
