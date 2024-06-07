/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_files_helper_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:22:14 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/07 17:34:39 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_file_helper	init_file_helper(char *str)
{
	t_file_helper	helper;

	helper.index = 0;
	helper.sq = 0;
	helper.dq = 0;
	helper.len = ft_strlen(str);
	helper.start = NULL;
	helper.new = NULL;
	helper.old = NULL;
	return (helper);
}

int	need_update_sq_dq(char *str, t_file_helper fh)
{
	if (str[fh.index] == '\'' || str[fh.index] == '\"')
		return (1);
	return (0);
}

int	need_file_node_all(char *str, t_file_helper fh)
{
	return (!(fh.sq) && !(fh.dq)
		&& (str[fh.index] == '>' || str[fh.index] == '<'));
}

int	need_file_node_normal(char *str, char *ch, t_file_helper fh)
{
	return (!fh.sq && !fh.dq && str[fh.index] == *ch);
}

void	update_sq_dq_file(char *str, t_file_helper *fh)
{
	if (str[(*fh).index] == '\"' && ((*fh).dq) == 0)
		((*fh).dq) = 1;
	else if (str[(*fh).index] == '\"')
		((*fh).dq) = 0;
	else if (str[(*fh).index] == '\'' && ((*fh).sq) == 0)
		((*fh).sq) = 1;
	else if (str[(*fh).index] == '\'')
		((*fh).sq) = 0;
}
