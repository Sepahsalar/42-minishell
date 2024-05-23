/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:46:38 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/23 12:30:02 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env_pack	run_builtin(t_cmd *cmd)
{
	t_env_pack	env_pack;

	env_pack = init_env_pack(cmd);
	if (same("echo", cmd->cmd_name))
		return (run_echo(cmd));
	else if (same("cd", cmd->cmd_name))
		return (run_cd(cmd));
	else if (same("pwd", cmd->cmd_name))
		return (run_pwd(cmd));
	else if (same("export", cmd->cmd_name))
		return (run_export(cmd));
	else if (same("unset", cmd->cmd_name))
		return (run_unset(cmd));
	else if (same("env", cmd->cmd_name))
		return (run_env(cmd));
	else if (same("exit", cmd->cmd_name))
		return (run_exit(cmd));
	else if (same("./minishell", cmd->cmd_name))
		return (run_minishell(cmd));
	return (env_pack);
}

int	is_builtin(t_cmd *cmd)
{
	// char	*builtin[9];
	char	*builtin[8];
	int		i;

	builtin[0] = "echo";
	builtin[1] = "cd";
	builtin[2] = "pwd";
	builtin[3] = "export";
	builtin[4] = "unset";
	builtin[5] = "env";
	builtin[6] = "exit";
	// builtin[7] = "./minishell";
	builtin[7] = NULL;
	i = 0;
	while (builtin[i])
	{
		if (same(builtin[i], cmd->cmd_name))
			return (i + 1);
		i++;
	}
	return (-1);
}
