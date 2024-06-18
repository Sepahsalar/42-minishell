/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:07:18 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/18 18:10:10 by asohrabi         ###   ########.fr       */
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

void	update_dollar_list(t_handle_dollar *hd_pointer, char *old_str)
{
	t_dollar		*last;
	t_dollar		*temp_dollar;
	// char			*temp_str;
	int				rel;
	int				changed_len;

	last = hd_pointer->dollar;
	while (last->next)
		last = last->next;
	temp_dollar = last;
	changed_len = ft_strlen(hd_pointer->str) - ft_strlen(old_str);
	// temp_str = hd_pointer->str;
	while (temp_dollar)
	{
		rel = temp_dollar->place - old_str;
		temp_dollar->place = hd_pointer->str + rel + changed_len;
		// temp_str = temp_dollar->place - 1;
		temp_dollar = temp_dollar->previous;
	}
	// hd_pointer->dollar = hd_pointer->dollar->next;
	// remove_previous_node(hd_pointer->dollar);
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
