/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env_cmd_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:09:33 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/15 14:00:42 by nnourine         ###   ########.fr       */
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

void	fill_original_env_cmd_list(t_cmd **cmd, t_env *original_env)
{
	t_cmd	*temp;

	temp = *cmd;
	while (temp)
	{
		temp->original_env = original_env;
		temp = temp->next;
	}
}
