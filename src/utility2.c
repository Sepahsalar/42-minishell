/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:04:15 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/30 16:45:48 by asohrabi         ###   ########.fr       */
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
	if (!str || !str[0])
		return (1);
	while (str[index])
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

t_hd_file	*remove_update(t_hd_file *hd, char *ch)
{
	char	*temp_str;
	char 	*temp_str2;
	int		len;
	t_file	*file;

	// printf("hd->str beginning remove update: %s\n", hd->str);
	len = ft_strlen(hd->str);
	// printf("remove update1: %s\n", hd->str);
	if (*ch == '>')
		hd->file->fd_operator = atoi_file(&(hd->str), hd->file->place, 1);
	else if (*ch == '<')
		hd->file->fd_operator = atoi_file(&(hd->str), hd->file->place, 0);
	// printf("hd->str after atoi file: %s\n", hd->str);
	// printf("remove update2: %s\n", hd->str);
	hd->file->place = hd->file->place + ft_strlen(hd->str) - len;
	temp_str = hd->str + hd->file->place;
	file = hd->file->next;
	while (file)
	{
		file->place = file->place + ft_strlen(hd->str) - len;
		file = file->next;
	}
	// printf("remove update3: %s\n", hd->str);
	if (*ch == '>' && *(temp_str + 1) == '>')
	{
		temp_str++;
		hd->file->append = 1;
	}
	else if (*ch == '>')
	{
		hd->file->trunc = 1;
	}
	else if (*ch == '<' && *(temp_str + 1) == '<')
	{
		// printf("temp_str: %s\n", temp_str);
		temp_str2 = strdup_modified(temp_str, "<<");
		hd->file->limiter = handling_quote(temp_str2);
		//free(temp_str2);
		// printf("hd->file->limiter: %s\n", hd->file->limiter);
		temp_str++;
	}
	else if (*ch == '<')
		hd->file->input = 1;
	// printf("remove update4: %s\n", hd->str);
	// printf("before the fucking dup str is: %s\n", hd->str);
	// printf("before the fucking dup file name is: %s\n", hd->file->raw);
	// printf("before the fucking dup temp_str is: %s\n", temp_str);
	hd->file->raw = strdup_modified(temp_str, ch);
	// printf("remove update5: %s\n", hd->str);
	// printf("after the fucking dup str is: %s\n", hd->str);
	// printf("after the fucking dup file name is: %s\n", hd->file->raw);
	hd->str = ft_remove(hd->str, hd->file->raw, hd->file);
	// printf("remove update6: %s\n", hd->str);
	// printf("hd->str at end: %s\n", hd->str);
	return (hd);
}

int	fill_files_helper(char *str, char *ch , t_cmd *cmd)
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
	// printf("hd->str: %s\n", hd->str);
	while (hd->file)
	{
		hd = remove_update(hd, ch);
		hd->file = hd->file->next;
	}
	cmd->current = ft_strdup(hd->str);
	// printf("cmd->current fill files helper: %s\n", cmd->current);
	if (*ch == '>')
		cmd->output = start;
	else
		cmd->input = start;
	return (0);
}

t_hd_file	*remove_update_all(t_hd_file *hd)
{
	char	*temp_str;

	temp_str = hd->str + hd->file->place;
	if (*(temp_str) == '>' && *(temp_str + 1) == '>')
	{
		// temp_str++;
		hd->file->append = 1;
		hd->file->raw = strdup_modified(temp_str, ">>");
	}
	else if (*(temp_str) == '>')
	{
		hd->file->trunc = 1;
		hd->file->raw = strdup_modified(temp_str, ">");
	}
	else if (*(temp_str) == '<' && *(temp_str + 1) != '<')
	{
		hd->file->input = 1;
		hd->file->raw = strdup_modified(temp_str, "<");
	}
	return (hd);
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
	// printf("cmd->current helper all: %s\n", cmd->current);
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
			if (str[index + 1] == '>' || str[index + 1] == '<')
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
	// cmd->current = ft_strdup(hd->str);
	cmd->all = start;
	return (0);
}
