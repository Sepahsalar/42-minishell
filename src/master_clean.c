/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:27:08 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/28 20:13:55 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	master_clean(char **raw_cmd, t_env *env, t_cmd *cmd, int exit_value)
{
	if (raw_cmd)
		clean_2d_char(raw_cmd);
	(void)env;
	(void)cmd;
	(void)exit_value;

	// if (env)
	// 	clean_env_list(env);
	// if (cmd)
	// 	clean_cmd_list(cmd);
	// if (exit_value != -1)
	// 	exit(exit_value);
}
