/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_files_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:29:11 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/04 13:54:59 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	fill_files_helper(char *str, char *ch, t_cmd *cmd)
{
	int			index;
	char		*sq;
	char		*dq;
	int			len;
	t_file		*start;
	t_file		*new;
	t_file  	*old;
	t_hd_file	*hd;

	sq = NULL;
	dq = NULL;
	hd = malloc(sizeof(t_hd_file));
	ft_memset(hd, 0, sizeof(t_hd_file));
	if (!str || *str == '\0')
		return (0);
	start = NULL;
	index = 0;
	len = ft_strlen(str);
	while (index < len)
	{
		if (str[index] == '\"' && dq == NULL)
			dq = &str[index];
		else if (str[index] == '\"')
			dq = NULL;
		else if (str[index] == '\'' && sq == NULL)
			sq = &str[index];
		else if (str[index] == '\'')
			sq = NULL;
		else if (!sq && !dq && str[index] == *ch)
		{
			new = create_file_node(index);
			if (start == NULL)
				start = new;
			else
				old->next = new;
			if (!new)
			{
				clean_file_list(start);
				return (1);
			}
			old = new;
			if (str[index + 1] == *ch)
				index++;
		}
		index++;
	}
	hd->file = start;
	hd->str = ft_strdup(str);
	while (hd->file)
	{
		hd = remove_update(hd, ch);
		hd->file = hd->file->next;
	}
	cmd->current = ft_strdup(hd->str);
	if (*ch == '>')
		cmd->output = start;
	else
		cmd->input = start;
	return (0);
}

int	fill_files_helper_all(t_cmd *cmd)
{
	int			index;
	char		*sq;
	char		*dq;
	int			len;
	t_file		*start;
	t_file		*new;
	t_file  	*old;
	t_hd_file	*hd;
	char        *str;

	sq = NULL;
	dq = NULL;
	str = cmd->current;
	hd = malloc(sizeof(t_hd_file));
	ft_memset(hd, 0, sizeof(t_hd_file));
	if (!str || *str == '\0')
		return (0);
	start = NULL;
	index = 0;
	len = ft_strlen(str);
	while (index < len)
	{
		if (str[index] == '\"' && dq == NULL)
			dq = &str[index];
		else if (str[index] == '\"')
			dq = NULL;
		else if (str[index] == '\'' && sq == NULL)
			sq = &str[index];
		else if (str[index] == '\'')
			sq = NULL;
		else if (!sq && !dq && (str[index] == '>' || str[index] == '<'))
		{
			new = create_file_node(index);
			if (start == NULL)
				start = new;
			else
				old->next = new;
			if (!new)
			{
				clean_file_list(start);
				return (1);
			}
			old = new;
			if ((str[index] == '>' && str[index + 1] == '>')
				|| (str[index] == '<' && str[index + 1] == '<'))
				index++;
		}
		index++;
	}
	hd->file = start;
	hd->str = ft_strdup(str);
	while (hd->file)
	{
		hd = remove_update_all(hd);
		hd->file = hd->file->next;
	}
	cmd->all = start;
	return (0);
}
