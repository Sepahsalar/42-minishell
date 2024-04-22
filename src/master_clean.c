/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:27:08 by nnourine          #+#    #+#             */
/*   Updated: 2024/04/22 12:01:53 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_master_clean(char **raw_cmd, t_env *env, t_cmd *cmd, int exit_value)
{
	if (raw_cmd)
		ft_clean_2d_char(raw_cmd);
	if (env)
		ft_clean_env_list(env);
	if (cmd)
		ft_clean_cmd_list(cmd);
	exit(exit_value);
}
