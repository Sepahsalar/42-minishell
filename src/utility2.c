/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:04:15 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/27 19:03:37 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	char_2d_count(char **array)
{
	int		counter;

	counter = 0;
	while (array[counter])
		counter++;
	return (counter);
}

int	cmd_count(t_cmd *cmd)
{
	int	count;

	if (!cmd)
		return (0);
	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

int	all_space(char *str)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
	{
		if (!ft_isspace(str[index]))
			return (0);
		index++;
	}
	return (1);
}

char	**copy_2d_char(char **src)
{
	char	**dest;
	int		i;

	i = 0;
	dest = (char **)malloc(sizeof(char *) * (char_2d_count(src) + 1));
	if (!dest)
		return (0);
	while (src[i])
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
			return (0);
		i++;
	}
	dest[i] = 0;
	return (dest);
}

t_hd_file	*remove_update(t_hd_file *hd, char *c)
{
	char	*temp_str;

	if (*c == '>')
		hd->file->fd_operator = atoi_file(&(hd->str), hd->file->place, 1);
	else if (*c == '<')
		hd->file->fd_operator = atoi_file(&(hd->str), hd->file->place, 0);
	temp_str = hd->str + hd->file->place;
	if (*c == '>' && *(temp_str + 1) == '>')
	{
		temp_str++;
		hd->file->append = 1;
	}
	else if (*c == '>')
	{
		hd->file->trunc = 1;
	}
	else if (*c == '<' && *(temp_str + 1) == '<')
	{
		hd->file->limiter = strdup_modified(temp_str, "<<");
		temp_str++;
	}
	else if (*c == '<')
		hd->file->input = 1;
	hd->file->raw = strdup_modified(temp_str, c);
	hd->str = ft_remove(hd->str, hd->file->raw, hd->file);
	return (hd);
}

int	fill_files_helper(char *str, char *c , t_cmd *cmd)
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
		else if (!sq && !dq && str[index] == *c)
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
			if (str[index + 1] == *c)
				index++;
		}
		index++;
	}
	hd->file = start;
	hd->str = ft_strdup(str);
	while (hd->file)
	{
		hd = remove_update(hd, c);
		hd->file = hd->file->next;
	}
	cmd->current = ft_strdup(hd->str);
	if (*c == '>')
		cmd->output = start;
	else
		cmd->input = start;
	return (0);
}
