/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_dollar_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:18:55 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/05 10:49:55 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sq_dq_updater(char *c, char **sq, char **dq)
{
	if (*c == '\'' && *sq)
		*sq = NULL;
	else if (*c == '\'')
		*sq = c;
	else if (*c == '\"' && *dq)
		*dq = NULL;
	else if (*c == '\"')
		*dq = c;
}

void	heredoc_updater(char *str, int *heredoc)
{
	if (ft_strnstr(str, "<<", 2) && *heredoc == 0)
		*heredoc = 1;
	else if (*str == ' ' && *heredoc == 1)
		*heredoc = 0;
}

t_dollar_helper	init_dollar_helper(void)
{
	t_dollar_helper	d;

	d.first = NULL;
	d.new = NULL;
	d.old = NULL;
	d.index = 0;
	d.sq = NULL;
	d.dq = NULL;
	d.heredoc = 0;
	d.type = 0;
	d.id = 0;
	return (d);
}

void	sq_dq_heredoc_update(char *arg, t_dollar_helper *d)
{
	sq_dq_updater(&arg[(*d).index], &((*d).sq), &((*d).dq));
	heredoc_updater(&arg[(*d).index], &((*d).heredoc));
}

int	should_create_node(char *arg, t_dollar_helper d)
{
	return (arg[d.index] && arg[d.index] == '$'
		&& (d.index < 1 || arg[d.index - 1] != '$'));
}

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
