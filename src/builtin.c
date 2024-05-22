/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:46:38 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/22 17:34:54 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env_pack	run_builtin(t_cmd *cmd)
{
	t_env_pack	env_pack;

	env_pack.env = cmd->env;
	env_pack.original_env = cmd->original_env;
	// if (ft_strlen("echo") == ft_strlen(cmd->cmd_name)
	// 	&& !ft_strncmp(cmd->cmd_name, "echo", ft_strlen("echo")))
	// 	return (run_echo(cmd));
	if (ft_strlen("cd") == ft_strlen(cmd->cmd_name)
		&& !ft_strncmp(cmd->cmd_name, "cd", ft_strlen("cd")))
		return (run_cd(cmd));
	if (ft_strlen("pwd") == ft_strlen(cmd->cmd_name)
		&& !ft_strncmp(cmd->cmd_name, "pwd", ft_strlen("pwd")))
		return (run_pwd(cmd));
	if (ft_strlen("export") == ft_strlen(cmd->cmd_name)
		&& !ft_strncmp(cmd->cmd_name, "export", ft_strlen("export")))
	{
		// run_export(cmd);
		return (run_export(cmd));// should be replaced with exit code of return
	}
	if (ft_strlen("unset") == ft_strlen(cmd->cmd_name)
		&& !ft_strncmp(cmd->cmd_name, "unset", ft_strlen("unset")))
		return (run_unset(cmd));
	if (ft_strlen("env") == ft_strlen(cmd->cmd_name)
		&& !ft_strncmp(cmd->cmd_name, "env", ft_strlen("env")))
		return (run_env(cmd));
	// if (ft_strlen("exit") == ft_strlen(cmd->cmd_name)
	// 	&& !ft_strncmp(cmd->cmd_name, "exit", ft_strlen("exit")))
	// 	return (run_exit(cmd));
	// if (ft_strlen("minishell") == ft_strlen(cmd->cmd_name)
	// 	&& !ft_strncmp(cmd->cmd_name, "minishell", ft_strlen("minishell")))
	// 	return (run_minishell(cmd));
	return (env_pack);
	// return (-1);
}

int	is_builtin(t_cmd *cmd)
{
	// char	*builtin[9];
	// int      i;

	// builtin[0] = "echo";
	// builtin[1] = "cd";
	// builtin[2] = "pwd";
	// builtin[3] = "export";
	// builtin[4] = "unset";
	// builtin[5] = "env";
	// builtin[6] = "exit";
	// builtin[7] = "minishell";
	// builtin[8] = NULL;
	// i = 0;
	// while (builtin[i])
	// {
	// 	if (ft_strlen(builtin[i]) == ft_strlen(cmd->cmd_name)
	// 		&& ft_strncmp(cmd->cmd_name, builtin[i], ft_strlen(builtin[i])))
	// 		return (i + 1);
	// 	i++;
	// }
	// return (-1);
	if (ft_strlen("cd") == ft_strlen(cmd->cmd_name)
		&& !ft_strncmp(cmd->cmd_name, "cd", ft_strlen("cd")))
		return (2);
	if (ft_strlen("pwd") == ft_strlen(cmd->cmd_name)
		&& !ft_strncmp(cmd->cmd_name, "pwd", ft_strlen("pwd")))
		return (3);
	if (ft_strlen("export") == ft_strlen(cmd->cmd_name)
		&& !ft_strncmp(cmd->cmd_name, "export", ft_strlen("export")))
		return (4);
	if (ft_strlen("unset") == ft_strlen(cmd->cmd_name)
		&& !ft_strncmp(cmd->cmd_name, "unset", ft_strlen("unset")))
		return (5);
	if (ft_strlen("env") == ft_strlen(cmd->cmd_name)
		&& !ft_strncmp(cmd->cmd_name, "env", ft_strlen("env")))
		return (6);
	// if (ft_strlen("minishell") == ft_strlen(cmd->cmd_name)
	// 	&& !ft_strncmp(cmd->cmd_name, "minishell", ft_strlen("minishell")))
	// 	return (8);
	return (-1);
}
