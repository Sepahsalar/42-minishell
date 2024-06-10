/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_files_helper_all.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:26:17 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/10 21:41:44 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	creating_all_node_process(char *str, t_file_helper *fh)
{
	(*fh).new = create_file_node((*fh).index);
	if (((*fh).start) == NULL)
		((*fh).start) = (*fh).new;
	else
		(*fh).old->next = (*fh).new;
	if (!(*fh).new)
	{
		clean_file_list(((*fh).start));
		return (1);
	}
	(*fh).old = (*fh).new;
	if ((str[(*fh).index] == '>' && str[(*fh).index + 1] == '>')
		|| (str[(*fh).index] == '<' && str[(*fh).index + 1] == '<'))
		(*fh).index++;
	return (0);
}

static long	fd_operator_all(t_hd_file *hd)
{
	char	c;
	long	fd_operator;
	char	*str_dup;
	int		place;

	fd_operator = -1;
	place = hd->file->place;
	c = hd->str[place];
	str_dup = ft_strdup(hd->str);
	//protection
	if (c == '>')
		fd_operator = atoi_file(&str_dup, place, 1);
	else if (c == '<')
		fd_operator = atoi_file(&str_dup, place, 0);
	//protection
	free(str_dup);
	return (fd_operator);
}

int	handle_hd_all(t_cmd *cmd, t_file **file)
{
	t_hd_file		*hd;

	hd = malloc(sizeof(t_hd_file));
	ft_memset(hd, 0, sizeof(t_hd_file));
	hd->file = *file;
	hd->str = ft_strdup(cmd->current);
	while (hd && hd->file)
	{
		hd->file->fd_operator = fd_operator_all(hd);
		//protection
		hd = remove_update_all(hd);
		//failiure return 1
		if (hd)
			hd->file = hd->file->next;
	}
	if (hd)
		free(hd->str);
	free(hd);
	return (0);
}

int	fill_files_helper_all(t_cmd *cmd)
{
	t_file_helper	fh;

	if (!cmd->current || *(cmd->current) == '\0')
		return (0);
	fh = init_file_helper(cmd->current);
	while (fh.index < fh.len)
	{
		if (need_update_sq_dq(cmd->current, fh))
			update_sq_dq_file(cmd->current, &fh);
		else if (need_file_node_all(cmd->current, fh))
		{
			if (creating_all_node_process(cmd->current, &fh))
				return (1);
		}
		fh.index++;
	}
	if (handle_hd_all(cmd, &(fh.start)))
		return (1);
	cmd->all = fh.start;
	return (0);
}
