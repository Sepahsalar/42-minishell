/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:27:08 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/10 21:02:38 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	master_clean(char **raw_cmd, t_cmd *cmd, int exit_value)
{

	(void)raw_cmd;
	(void)cmd;
	// t_cmd *start;
	
	// if (raw_cmd)
	// 	clean_2d_char(raw_cmd);
	// if (ft_atoi(value_finder(cmd->original_env, "fd_stdin")) >= 0)
	// 	close(ft_atoi(value_finder(cmd->original_env, "fd_stdin")));
	// if (ft_atoi(value_finder(cmd->original_env, "fd_stdout")) >= 0)
	// 	close(ft_atoi(value_finder(cmd->original_env, "fd_stdout")));
	// if (cmd->env)
	// 	clean_env_list(cmd->env);
	// if (cmd->original_env)
	// 	clean_env_list(cmd->original_env);
	// if (cmd)
	// {
	// 	while (cmd)
	// 	{
	// 		start = cmd;
	// 		cmd = cmd->previous;
	// 	}
	// 	cmd = start;
	// 	while (cmd)
	// 	{
	// 		clean_cmd_list(cmd);
	// 		cmd = cmd->next;
	// 	}
	// }
	
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	change_mode(RUNNING_COMMAND);
	if (exit_value != -1)
		exit(exit_value);
}
