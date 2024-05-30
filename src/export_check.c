/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:43:44 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/30 14:47:20 by nnourine         ###   ########.fr       */
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
		if (!ft_isalpha(*str) && *str != '_' && *str != '=' && *str != '+')
			return (0);
		str++;
	}
	return (1);
}

int	export_check_key(char *str)
{
	char	*find;

	find = ft_strchr(str, '=');
	if (find == str)
		return (0);
	while (*str && (str < find || !find))
	{
		if (!ft_isalpha(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

