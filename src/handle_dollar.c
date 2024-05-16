/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:07:18 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/16 19:42:50 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*handle_dollar_str(t_cmd *cmd, t_handle_dollar hd)
{
	char	*new_str;
	char	*sq_location;
	int		index;
	char	*inside;
	char	*handeled_inside;

	if (hd.dollar->type == 1)
	{
		index = 0;
		while ((hd.str + index) != hd.dollar->place)
		{
			if (hd.str[index] == '\'')
				sq_location = &hd.str[index];
			index++;
		}
		// printf("hd.str -> type 2 = %s | place of $ is = %s\n", hd.str, hd.dollar->place);
		char *real_location = hd.dollar->place;
		int real_index = real_location - sq_location;
		inside = inside_double_quote(sq_location);
		char *inside_location = inside + real_index - 1;
		printf("inside: %s\n", inside);
		handeled_inside = expand_dollar_helper(cmd, inside, inside_location);
		printf("handeled_inside: %s\n", handeled_inside);
		new_str = replace_inside(hd.str, sq_location, inside, handeled_inside);
		free(inside);
		return (new_str);
	}
	else if (hd.dollar->type == 4)
	{
		// printf("hd.str -> type 4 = %s | place of $ is = %s\n", hd.str, hd.dollar->place);
		new_str = expand_dollar_helper(cmd, hd.str, hd.dollar->place);
		return (new_str);
	}
	else
	{
		// printf("hd.str -> type %d = %s | place of $ is = %s\n",hd.dollar->type, hd.str, hd.dollar->place);
		new_str = expand_dollar_helper(cmd, hd.str, hd.dollar->place);
		return (new_str);
	}
}
void	update_dollar_list(t_handle_dollar *hd_pointer)
{
	t_dollar		*last;
	t_dollar		*temp_dollar;
	char			*temp_str;

	last = hd_pointer->dollar;
	while (last->next)
		last = last->next;
	temp_dollar = last;
	temp_str = hd_pointer->str;
	while (temp_dollar->id > hd_pointer->dollar->id)
	{
		temp_dollar->place = ft_strrchr(temp_str, '$');
		temp_str = temp_dollar->place - 1;
		temp_dollar = temp_dollar->previous;
	}
	hd_pointer->dollar = hd_pointer->dollar->next;
}

void	handle_hd(t_cmd *cmd, t_handle_dollar *hd_pointer)
{
	char			*temp;

	temp = hd_pointer->str;
	if (hd_pointer->dollar->type != -1 && hd_pointer->dollar->type != 2
		&& hd_pointer->dollar->type != 3)
	{
		hd_pointer->str = handle_dollar_str(cmd, *hd_pointer);
		update_dollar_list(hd_pointer);
		// free(temp);
	}
	else
		hd_pointer->dollar = hd_pointer->dollar->next;
}

int	handle_dollar_struct(t_cmd *cmd)
{
	t_handle_dollar	hd;
	t_dollar		*temp;
	char			*str;

	str = cmd->current;
	if (ft_strchr(str, '$'))
	{
		hd.dollar = create_fill_dollar_list(str);
		temp = hd.dollar;
		hd.str = str;
		while (hd.dollar)
		{
			handle_hd(cmd, &hd);
			if (hd.str == NULL)
				return (1);
		}
		//dollar_list should be cleand
		clean_dollar_list(temp);
		cmd->current = hd.str;
		//we have to remove " at this step???
	}
	return (0);
}
