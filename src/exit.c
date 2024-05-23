/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:49:01 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/23 11:46:10 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env_pack	run_exit(t_cmd *cmd)
{
	t_env_pack	env_pack;
	t_atol		exit_code;

	exit_code.num = 0;
	exit_code.is_error = 0;
	env_pack = init_env_pack(cmd);
	printf("exit\n");
	if (cmd->args[2])
	{
		printf("bash: exit: too many arguments\n");
		exit (1);
	}
	if (cmd->args[1])
		exit_code = atol_exit(cmd->args[1]);
	else
		exit_code.num = 0;
	if (exit_code.is_error == 1)
	{
		printf("bash: exit: %s: numeric argument required\n", cmd->args[1]);
		exit (255);
	}
	exit_code.num = exit_code.num % 256;
	exit (exit_code.num);
	return (env_pack);
}

void	run_exit_eof(t_env *env, int fd_stdin, int fd_stdout)
{
	int	exit_code;

	printf (ANSI_MOVE_UP ANSI_COLOR_GREEN "[ASAL]" ANSI_COLOR_RESET"$ exit\n");
	exit_code = ft_atoi(value_finder(env, "exit_code"));
	close(fd_stdin);
	close(fd_stdout);
	//master_clean needed
	exit (exit_code);
}
