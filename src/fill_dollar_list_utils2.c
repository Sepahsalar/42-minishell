/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_dollar_list_utils2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:17:17 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/05 11:20:04 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	sq_dq_updater(char *c, char **sq, char **dq)
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

static void	heredoc_updater(char *str, int *heredoc)
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
