/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:09:24 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/19 12:23:34 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*expand_pid(char *str, char *start, char *temp, int count)
{
	char	*new;
	int		len;
	char	*dst;
	int		temp_count;

	if (!count)
		return (str);
	len = ft_strlen(str) + (count *(ft_strlen(temp) - 2));
	new = malloc(len + 1);
	if (!new)
		return (NULL);
	new[len] = '\0';
	dst = new;
	ft_memcpy(dst, str, (start - str));
	dst = dst + (start - str);
	temp_count = count;
	while (count)
	{
		ft_memcpy(dst, temp, ft_strlen(temp));
		dst += ft_strlen(temp);
		count--;
	}
	ft_memcpy(dst, start + (2 * temp_count),
		ft_strlen(start + (2 * temp_count)));
	return (new);
}

static void	expand_two_dollars_helper(t_cmd *cmd, char **str,
	char **find, int count)
{
	int		reletive_index;
	char	*temp;

	temp = cmd->original_env->next->value;
	reletive_index = (*find) - (*str);
	if (count)
	{
		(*str) = expand_pid((*str), (*find), temp, count);
		if (!*str)
			master_clean(NULL, cmd, EXIT_FAILURE);
		(*find) = (*str) + reletive_index + (ft_strlen(temp) * count);
	}
	else
	{
	    *str = ft_strdup(*str);
		if (!*str)
			master_clean(NULL, cmd, EXIT_FAILURE);
		(*find) = (*str) + reletive_index;
	}
}

void	expand_two_dollars(t_cmd *cmd, char **str,
	char **find, int *remained_dollar)
{
	int		index;
	int		count;

	count = 0;
	index = 0;
	while ((*find)[index] && (*find)[index] == '$')
	{
		count++;
		index++;
	}
	(*remained_dollar) = count % 2;
	count = count / 2;
	expand_two_dollars_helper(cmd, str, find, count);
}

int	no_need_more_expand(int remain_dollar, char *find, int type)
{
	if (!remain_dollar)
		return (1);
	return ((!*find) || (find && (*(find + 1) == '\0'
				|| *(find + 1) == ' ' || *(find + 1) == '='
				|| (type == 2 && (*(find + 1) == '\''
						|| *(find + 1) == '\"')))));
}
