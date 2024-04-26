/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:39:49 by nnourine          #+#    #+#             */
/*   Updated: 2024/04/26 13:39:41 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_file	*ft_last_file(t_file *head)
{
	t_file	*tmp;
	t_file	*last;

	tmp = head;
	last = tmp;
	while (tmp)
	{
		last = tmp;
		tmp = tmp->next;
	}
	return (last);
}

t_cmd	*ft_last_cmd(t_cmd *head)
{
	t_cmd	*tmp;
	t_cmd	*last;

	tmp = head;
	while (tmp)
	{
		last = tmp;
		tmp = tmp->next;
	}
	return (last);
}
