/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:56:25 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/19 17:29:07 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*full_path_finder(char *pwd, char *arg, t_cmd *cmd)
{
	char	*temp1;
	char	*temp2;
	char	*home;

	home = value_finder(cmd->original_env, "HOME");
	if (!arg)
		return (ft_strdup(home));
	else if (arg[0] == '~')
		return (ft_strjoin(home, (arg + 1)));
	else if (arg[0] != '/')
	{
		temp1 = ft_strjoin(pwd, "/");
		if (!temp1)
			return (NULL);
		temp2 = ft_strjoin(temp1, arg);
		free(temp1);
		return (temp2);
	}
	else
		return (ft_strdup(arg));
}

t_env_pack	run_cd_helper(char *full_path, t_cmd *cmd, t_env_pack env_pack)
{
	char		*new_pwd;

	if (!full_path)
		master_clean(NULL, cmd, EXIT_FAILURE);
	if (chdir(full_path) == -1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		env_pack.original_env = export_original(cmd->original_env, 1);
	}
	else
	{
		new_pwd = getcwd(NULL, 0);
		if (!new_pwd)
			master_clean(NULL, cmd, EXIT_FAILURE);
		env_pack.env = custom_export(env_pack.env, "PWD", new_pwd);
		free(new_pwd);
		env_pack.original_env = export_original(cmd->original_env, 0);
	}
	free(full_path);
	return (env_pack);
}

char	*del_folder_double_dot(t_cmd *cmd, t_env_pack env_pack)
{
	char	*full_path;

	if (cmd->args[1] && same(cmd->args[1], ".."))
		full_path = path_only_one_double_dot(env_pack);
	else
		full_path = path_start_with_double_dot(cmd, env_pack);
	return (full_path);
}

t_env_pack	run_cd(t_cmd *cmd)
{
	char		*old_pwd;
	t_env_pack	env_pack;
	char		*full_path;

	env_pack = init_env_pack(cmd);
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		if (same(cmd->args[1], ".") && errno == ENOENT)
			return (del_folder_one_dot(env_pack, cmd));
		else if (start_with_double_dot(cmd->args[1]))
			full_path = del_folder_double_dot(cmd, env_pack);
		else if (cmd->args[1] == NULL)
			full_path = ft_strdup(value_finder(cmd->original_env, "HOME"));
		else
			return (del_folder_else(env_pack, cmd));
	}
	else
	{
		env_pack.env = custom_export(env_pack.env, "OLDPWD", old_pwd);
		full_path = full_path_finder(old_pwd, cmd->args[1], cmd);
		free(old_pwd);
	}
	env_pack = run_cd_helper(full_path, cmd, env_pack);
	return (env_pack);
}
