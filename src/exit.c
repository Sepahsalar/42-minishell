/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:49:01 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/18 10:45:34 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	run_exit_error(t_cmd *cmd)
{
	ft_putstr_fd("bash: exit: ", 2);
	ft_putstr_fd(cmd->args[1], 2);
	ft_putendl_fd(": numeric argument required", 2);
	exit(2);
}

t_env_pack	run_exit(t_cmd *cmd)
{
	t_env_pack	env_pack;
	t_atol		exit_code;
	int			count;

	exit_code.num = 0;
	exit_code.is_error = 0;
	env_pack = init_env_pack(cmd);
	if (!cmd->child_builtin)
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
		run_exit_error(cmd);
	exit_code.num = exit_code.num % 256;
	exit(exit_code.num);
	return (env_pack);
}

void	run_exit_eof(t_env *env)
{
	int	exit_code;

	printf(ANSI_COLOR_GREEN "[ASAL]" ANSI_COLOR_RESET"$ exit\n");
	exit_code = ft_atoi(value_finder(env, "exit_code"));
	clean_env_list(env);
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		exit(1);
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		exit(1);
	if (change_mode(RUNNING_COMMAND))
		exit(1);
	exit(exit_code);
}
