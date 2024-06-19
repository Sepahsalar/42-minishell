/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:21:36 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/19 11:40:18 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_unique(t_last_file *first, t_file *temp)
{
	t_last_file	*node;

	if (!first)
		return (1);
	node = first;
	while (node)
	{
		if (node->file->fd_operator == temp->fd_operator)
			return (0);
		node = node->next;
	}
	return (1);
}

t_hd_file	*remove_update_all(t_hd_file *hd)
{
	char	*temp_str;
	
	temp_str = hd->str + hd->file->place;
	if (*(temp_str) == '>' && *(temp_str + 1) == '>')
	{
		hd->file->append = 1;
		hd->file->raw = strdup_modified(temp_str, ">>");
		if (!hd->file->raw)
		{
			clean_file_list(hd->file);
			free(hd->str);
			free(hd);
		    return (0);
		}
	}
	else if (*(temp_str) == '>')
	{
		hd->file->trunc = 1;
		hd->file->raw = strdup_modified(temp_str, ">");
		if (!hd->file->raw)
		{
			clean_file_list(hd->file);
			free(hd->str);
			free(hd);
		    return (0);
		}
	}
	else if (*(temp_str) == '<' && *(temp_str + 1) != '<')
	{
		hd->file->input = 1;
		hd->file->raw = strdup_modified(temp_str, "<");
		if (!hd->file->raw)
		{
			clean_file_list(hd->file);
			free(hd->str);
			free(hd);
		    return (0);
		}
	}
	return (hd);
}

static t_hd_file	*remove_update_con(t_hd_file *hd, char *ch, char *temp_str)
{
	char	*temp_str2;

	if (*ch == '>' && *(temp_str + 1) == '>')
	{
		temp_str++;
		hd->file->append = 1;
	}
	else if (*ch == '>')
		hd->file->trunc = 1;
	else if (*ch == '<' && *(temp_str + 1) == '<')
	{
		temp_str2 = strdup_modified(temp_str, "<<");
		if (!temp_str2)
			return (0);
		hd->file->limiter = handling_quote(temp_str2);
		if (!hd->file->limiter)
			return (0);
		free(temp_str2);
		temp_str++;
	}
	else if (*ch == '<')
		hd->file->input = 1;
	hd->file->raw = strdup_modified(temp_str, ch);
	if (!hd->file->raw)
		return (0);
	return (hd);
}

static t_hd_file	*fd_operator(t_hd_file *hd, char *ch)
{
	if (*ch == '>')
		hd->file->fd_operator = atoi_file(&(hd->str), hd->file->place, 1);
	else if (*ch == '<')
		hd->file->fd_operator = atoi_file(&(hd->str), hd->file->place, 0);
	// if (hd->file->fd_operator == -3)
	//     return (NULL);
	return (hd);
}

t_hd_file	*remove_update(t_hd_file *hd, char *ch)
{
	char	*temp_str;
	int		len;
	t_file	*file;

	len = ft_strlen(hd->str);
	hd = fd_operator(hd, ch);
	if (!hd)
	    return (NULL);
	hd->file->place = hd->file->place + ft_strlen(hd->str) - len;
	temp_str = hd->str + hd->file->place;
	file = hd->file->next;
	while (file)
	{
		file->place = file->place + ft_strlen(hd->str) - len;
		file = file->next;
	}
	hd = remove_update_con(hd, ch, temp_str);
	if (!hd)
		return (0);
	temp_str = hd->str;
	hd->str = ft_remove(hd->str, hd->file->raw, hd->file);
	free(temp_str);
	if (!hd->str)
		return (0);
	return (hd);
}
