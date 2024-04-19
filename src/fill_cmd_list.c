/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:43:39 by nnourine          #+#    #+#             */
/*   Updated: 2024/04/19 11:00:49 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*ft_fill_cmd_list(char **raw_cmd, t_env *env)
{
	t_cmd	*cmd;
	int		cmd_count;

	cmd_count = ft_char_2d_count(raw_cmd);
	cmd = ft_create_cmd_list(cmd_count);
	if (!cmd)
		ft_master_clean(raw_cmd, env, 0, EXIT_FAILURE);
	ft_fill_index_cmd_list(&cmd);
	if (ft_fill_raw_cmd_list(&cmd, raw_cmd))
		ft_master_clean(raw_cmd, env, cmd, EXIT_FAILURE);
	if (ft_fill_heredoc_cmd_list(&cmd))
		ft_master_clean(raw_cmd, env, cmd, EXIT_FAILURE);
	return (cmd);
}
