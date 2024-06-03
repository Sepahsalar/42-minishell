/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_dollar_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:18:55 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/03 19:22:59 by asohrabi         ###   ########.fr       */
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

t_dollar	*fill_dollar_list(char *arg)
{
	t_dollar	*first;
	t_dollar	*new;
	t_dollar	*old;
	int			index;
	char		*sq;
	char		*dq;
	int			heredoc;
	int			type;
	int			id;

	if (!arg)
		return (0);
	index = 0;
	sq = NULL;
	dq = NULL;
	heredoc = 0;
	id = 0;
	while (index < (int)ft_strlen(arg))
	{
		sq_dq_updater(&arg[index], &sq, &dq);
		heredoc_updater(&arg[index], &heredoc);
		if (arg[index] && arg[index] == '$'
			&& (index < 1 || arg[index - 1] != '$'))
		{
			type = type_finder(sq, dq, heredoc);
			id++;
			new = create_dollar_node(id, &arg[index], type);
			if (id == 1)
				first = new;
			if (!new)
				return (clean_dollar_list(first));
			if (id != 1)
			{
				new->previous = old;
				old->next = new;
			}
			old = new;
		}
		index++;
	}
	return (first);
}
