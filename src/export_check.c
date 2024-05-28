/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:43:44 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/28 13:07:34 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	export_check(char *str)
{
	char	*find;

	find = ft_strchr(str, '=');
	if (find == str)
		return (0);
	while (*str && (str < find || !find))
	{
		if (!ft_isalpha(*str) && *str != '_' && *str != '=')
			return (0);
		str++;
	}
	return (1);
}
