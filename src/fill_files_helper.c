/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_files_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:29:11 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/05 10:52:51 by asohrabi         ###   ########.fr       */
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

int	handle_hd_normal(t_file **file, char *str, char *ch, t_cmd *cmd)
{
	t_hd_file	*hd;

	hd = malloc(sizeof(t_hd_file));
	ft_memset(hd, 0, sizeof(t_hd_file));
	hd->file = *file;
	hd->str = ft_strdup(str);
	while (hd->file)
	{
		hd = remove_update(hd, ch);
		//return 1 if failed
		hd->file = hd->file->next;
	}
	cmd->current = ft_strdup(hd->str);
	if (*ch == '>')
		cmd->output = *file;
	else
		cmd->input = *file;
	return (0);
}

int	creating_normal_node_process(char *str, char *ch, t_file_helper *fh)
{
	(*fh).new = create_file_node((*fh).index);
	if ((*fh).start == NULL)
		(*fh).start = (*fh).new;
	else
		(*fh).old->next = (*fh).new;
	if (!(*fh).new)
	{
		clean_file_list((*fh).start);
		return (1);
	}
	(*fh).old = (*fh).new;
	if (str[(*fh).index + 1] == *ch)
		(*fh).index++;
	return (0);
}

int	fill_files_helper(char *str, char *ch, t_cmd *cmd)
{
	t_file_helper	fh;

	if (!cmd->current || *(cmd->current) == '\0')
		return (0);
	fh = init_file_helper(cmd->current);
	while (fh.index < fh.len)
	{
		if (need_update_sq_dq(cmd->current, fh))
			update_sq_dq_file(cmd->current, &fh);
		else if (need_file_node_normal(str, ch, fh))
		{
			if (creating_normal_node_process(str, ch, &fh))
				return (1);
		}
		fh.index++;
	}
	if (handle_hd_normal(&(fh.start), str, ch, cmd))
		return (1);
	return (0);
}

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

int	handle_hd_all(t_cmd *cmd, t_file **file)
{
	t_hd_file		*hd;

	hd = malloc(sizeof(t_hd_file));
	ft_memset(hd, 0, sizeof(t_hd_file));
	hd->file = *file;
	hd->str = ft_strdup(cmd->current);
	while (hd->file)
	{
		hd = remove_update_all(hd);
		//failiure return 1
		hd->file = hd->file->next;
	}
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
