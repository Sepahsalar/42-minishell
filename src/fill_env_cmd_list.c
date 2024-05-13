/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env_cmd_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:09:33 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/13 18:09:09 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	fill_env_cmd_list(t_cmd **cmd, t_env *env)
{
	t_cmd	*temp;

	temp = *cmd;
	while (temp)
	{
		temp->env = env;
		temp = temp->next;
	}
}
