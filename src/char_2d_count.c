/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_2d_count.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:57:36 by nnourine          #+#    #+#             */
/*   Updated: 2024/04/19 10:33:09 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_char_2d_count(char **array)
{
	int		counter;

	counter = 0;
	while (array[counter])
		counter++;
	return (counter);
}
