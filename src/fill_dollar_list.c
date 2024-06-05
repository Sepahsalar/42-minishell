/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_dollar_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:18:55 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/05 11:17:13 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	node_creating_process(char *arg, t_dollar_helper *d)
{
	(*d).type = type_finder(((*d).sq), ((*d).dq), ((*d).heredoc));
	((*d).id)++;
	(*d).new = create_dollar_node(((*d).id), &arg[(*d).index], (*d).type);
	if (((*d).id) == 1)
		(*d).first = (*d).new;
	if (!(*d).new)
	{
		clean_dollar_list((*d).first);
		return (1);
	}
	if (((*d).id) != 1)
	{
		((*d).new)->previous = (*d).old;
		((*d).old)->next = (*d).new;
	}
	(*d).old = (*d).new;
	return (0);
}

t_dollar	*fill_dollar_list(char *arg)
{
	t_dollar_helper	d;

	if (!arg)
		return (0);
	d = init_dollar_helper();
	while (d.index < (int)ft_strlen(arg))
	{
		sq_dq_heredoc_update(arg, &d);
		if (should_create_node(arg, d))
		{
			if (node_creating_process(arg, &d))
				return (NULL);
		}
		d.index++;
	}
	return (d.first);
}
