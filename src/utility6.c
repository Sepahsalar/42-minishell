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

t_hd_file	*remove_update_all_helper_1(t_hd_file *hd)
{
	char	*temp_str;

	temp_str = hd->str + hd->file->place;
	hd->file->append = 1;
	hd->file->raw = strdup_modified(temp_str, ">>");
	if (!hd->file->raw)
	{
		clean_file_list(hd->file);
		free(hd->str);
		free(hd);
		return (0);
	}
	return (hd);
}

t_hd_file	*remove_update_all_helper_2(t_hd_file *hd)
{
	char	*temp_str;

	temp_str = hd->str + hd->file->place;
	hd->file->trunc = 1;
	hd->file->raw = strdup_modified(temp_str, ">");
	if (!hd->file->raw)
	{
		clean_file_list(hd->file);
		free(hd->str);
		free(hd);
		return (0);
	}
	return (hd);
}

t_hd_file	*remove_update_all_helper_3(t_hd_file *hd)
{
	char	*temp_str;

	temp_str = hd->str + hd->file->place;
	hd->file->input = 1;
	hd->file->raw = strdup_modified(temp_str, "<");
	if (!hd->file->raw)
	{
		clean_file_list(hd->file);
		free(hd->str);
		free(hd);
		return (0);
	}
	return (hd);
}

t_hd_file	*remove_update_all(t_hd_file *hd)
{
	char	*temp_str;

	temp_str = hd->str + hd->file->place;
	if (*(temp_str) == '>' && *(temp_str + 1) == '>')
		return (remove_update_all_helper_1(hd));
	else if (*(temp_str) == '>')
		return (remove_update_all_helper_2(hd));
	else if (*(temp_str) == '<' && *(temp_str + 1) != '<')
		return (remove_update_all_helper_3(hd));
	return (hd);
}