/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_palce_type_dollar.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:31:42 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/16 18:52:06 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clean_dollar_node(t_dollar *node)
{
	if (node)
		free (node);
}

t_dollar	*clean_dollar_list(t_dollar *first)
{
	t_dollar	*node;
	t_dollar	*temp;

	node = first;
	while (node)
	{
		temp = node->next;
		clean_dollar_node(node);
		node = temp;
	}
	return (0);
}

t_dollar	*create_dollar_node(int id, char *place, int type)
{
	t_dollar			*new;

	new = malloc(sizeof(t_dollar));
	if (!new)
		return (0);
	new->id = id;
	new->place = place;
	new->type = type;
	new->next = NULL;
	new->previous = NULL;
	return (new);
}

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

int	type_finder(char *sq, char *dq, int heredoc)
{
	if (heredoc)
		return (-1);
	if (!sq && !dq)
		return (5);
	else if (!sq && dq)
		return (4);
	else if (sq && !dq)
		return (3);
	else if (sq < dq)
		return (2);
	else
		return (1);
}

t_dollar	*create_fill_dollar_list(char *arg)
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
		// printf("for char : %c -> sq: %s , dq: %s\n", arg[index], sq, dq);
		heredoc_updater(&arg[index], &heredoc);
		if (arg[index] == '$')
		{
			// printf("sq: %s , dq: %s\n", sq, dq);
			type = type_finder(sq, dq, heredoc);
			// printf("type: %d\n", type);
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
