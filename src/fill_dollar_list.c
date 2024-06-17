/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_dollar_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:18:55 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/17 14:09:13 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	node_creating_process(char *arg, t_dollar_helper *dh)
{
	(*dh).type = type_finder(((*dh).sq), ((*dh).dq), ((*dh).heredoc));
	((*dh).id)++;
	(*dh).new = create_dollar_node(((*dh).id), &arg[(*dh).index], (*dh).type);
	if (((*dh).id) == 1)
		(*dh).first = (*dh).new;
	if (!(*dh).new)
	{
		clean_dollar_list((*dh).first);
		return (1);
	}
	if (((*dh).id) != 1)
	{
		((*dh).new)->previous = (*dh).old;
		((*dh).old)->next = (*dh).new;
	}
	(*dh).old = (*dh).new;
	return (0);
}

t_dollar	*fill_dollar_list(char *arg)
{
	t_dollar_helper	dh;

	if (!arg)
		return (0);
	dh = init_dollar_helper();
	while (dh.index < (int)ft_strlen(arg))
	{
		sq_dq_heredoc_update(arg, &dh);
		if (should_create_node(arg, dh))
		{
			if (node_creating_process(arg, &dh))
				return (NULL);
		}
		dh.index++;
	}
	return (dh.first);
}
