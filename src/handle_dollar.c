/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:07:18 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/19 16:39:23 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*handle_dollar_str(t_cmd *cmd, t_handle_dollar hd)
{
	char	*new_str;

	new_str = expand_dollar_helper(cmd, hd.str,
			hd.dollar->place, hd.dollar->type);
	return (new_str);
}

static t_dollar	*init_dollar_last(t_handle_dollar *hd_pointer)
{
	t_dollar	*last;

	last = hd_pointer->dollar;
	while (last->next)
		last = last->next;
	return (last);
}

void	update_dollar_list(t_handle_dollar *hd_pointer, char *old_str)
{
	t_dollar	*temp_dollar;
	int			rel;
	int			changed_len;

	temp_dollar = init_dollar_last(hd_pointer);
	changed_len = ft_strlen(hd_pointer->str) - ft_strlen(old_str);
	while (temp_dollar)
	{
		rel = temp_dollar->place - old_str;
		temp_dollar->place = hd_pointer->str + rel + changed_len;
		temp_dollar = temp_dollar->previous;
	}
	if (hd_pointer->dollar->next)
	{
		hd_pointer->dollar = hd_pointer->dollar->next;
		remove_previous_node(hd_pointer->dollar);
	}
	else
	{
		free(hd_pointer->dollar);
		hd_pointer->dollar = NULL;
	}
}

void	handle_hd(t_cmd *cmd, t_handle_dollar *hd_pointer)
{
	char			*temp;

	temp = hd_pointer->str;
	if (hd_pointer->dollar->type != -1 && hd_pointer->dollar->type != 1)
	{
		hd_pointer->str = handle_dollar_str(cmd, *hd_pointer);
		if (!hd_pointer->str)
			master_clean(NULL, cmd, EXIT_FAILURE);
		update_dollar_list(hd_pointer, temp);
		free(temp);
	}
	else
	{
		if (hd_pointer->dollar->next)
		{
			hd_pointer->dollar = hd_pointer->dollar->next;
			remove_previous_node(hd_pointer->dollar);
		}
		else
		{
			free(hd_pointer->dollar);
			hd_pointer->dollar = NULL;
		}
	}
}

int	handle_dollar_struct(t_cmd *cmd)
{
	t_handle_dollar	hd;
	char			*str;

	str = cmd->current;
	if (ft_strchr(str, '$'))
	{
		hd.dollar = fill_dollar_list(str);
		if (!hd.dollar)
			master_clean(NULL, cmd, EXIT_FAILURE);
		hd.str = str;
		while (hd.dollar)
		{
			handle_hd(cmd, &hd);
			if (hd.str == NULL)
				return (1);
		}
		cmd->current = hd.str;
	}
	return (0);
}
