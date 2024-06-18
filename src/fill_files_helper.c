/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_files_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:29:11 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/18 13:57:55 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_hd_normal(t_file **file, char *str, char *ch, t_cmd *cmd)
{
	t_hd_file	*hd;
	char		*temp;

	hd = malloc(sizeof(t_hd_file));
	if (!hd)
		master_clean(NULL, cmd, EXIT_FAILURE);
	ft_memset(hd, 0, sizeof(t_hd_file));
	hd->file = *file;
	hd->str = ft_strdup(str);
	if(!hd->str)
	{
		free(hd);
		master_clean(NULL, cmd, EXIT_FAILURE);
	}
	while (hd && hd->file)
	{
		hd = remove_update(hd, ch);
		// if (!hd)
		// 	master_clean(NULL, cmd, EXIT_FAILURE);
		if (hd && hd->file)
			hd->file = hd->file->next;
	}
	temp = cmd->current;
	if (hd)
		cmd->current = ft_strdup(hd->str);
	free(temp);
	if (*ch == '>')
		cmd->output = *file;
	else
		cmd->input = *file;
	if (hd)
		free(hd->str);
	free(hd);
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

	if (cmd && (!cmd->current || *(cmd->current) == '\0'))
		return (0);
	fh = init_file_helper(cmd->current);
	while (fh.index < fh.len)
	{
		if (cmd && need_update_sq_dq(cmd->current, fh))
			update_sq_dq_file(cmd->current, &fh);
		else if (need_file_node_normal(str, ch, fh))
			if (creating_normal_node_process(str, ch, &fh))
				return (1);
		fh.index++;
	}
	if (handle_hd_normal(&(fh.start), str, ch, cmd))
		return (1);
	return (0);
}
