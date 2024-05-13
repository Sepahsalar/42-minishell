/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:27:08 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/13 18:19:38 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	master_clean(char **raw_cmd, t_env *env, t_cmd *cmd, int exit_value)
{
	if (raw_cmd)
		clean_2d_char(raw_cmd);
	(void)env;
	(void)cmd;

	// if (env)
	// 	clean_env_list(env);
	// if (cmd)
	// 	clean_cmd_list(cmd);
	if (exit_value != -1)
		exit(exit_value);
}
