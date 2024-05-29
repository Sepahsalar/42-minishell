/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:49:01 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/29 14:29:54 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env_pack	run_exit(t_cmd *cmd)
{
	t_env_pack	env_pack;
	t_atol		exit_code;
	int         count;

	exit_code.num = 0;
	exit_code.is_error = 0;
	env_pack = init_env_pack(cmd);
	ft_putendl_fd("exit", 2);
	count = char_2d_count(cmd->args);
	if (count > 2)
	{
		ft_putendl_fd("bash: exit: too many arguments", 2);
		env_pack.original_env = export_original(env_pack.original_env, 1);
		return (env_pack);
	}
	else if (count == 2)
		exit_code = atol_exit(cmd->args[1]);
	else
		exit_code.num = ft_atoi(cmd->original_env->value);
	if (exit_code.is_error == 1)
	{
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(255);
	}
	exit_code.num = exit_code.num % 256;
	exit(exit_code.num);
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
