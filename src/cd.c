/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:56:25 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/05 14:45:28 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*custom_export(t_env *env, char *key, char *value)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (same(temp->key, key))
			break ;
		temp = temp->next;
	}
	if (temp)
	{
		free(temp->value);
		temp->value = ft_strdup(value);
	}
	else
		add_node_front(&env, ft_strdup(key), ft_strdup(value));
	return (env);
}

char	*full_path_finder(char *pwd, char *arg, char *home)
{
	char	*temp1;
	char	*temp2;

	if (!arg)
		return (ft_strdup(home));
	else if (arg[0] == '~')
		return (ft_strjoin(home, (arg + 1)));
	else if (arg[0] != '/')
	{
		temp1 = ft_strjoin(pwd, "/");
		temp2 = ft_strjoin(temp1, arg);
		free(temp1);
		return (temp2);
	}
	else
		return (ft_strdup(arg));
}

char	*value_finder(t_env *env, char *key)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (same(temp->key, key))
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

t_env_pack	run_cd_helper(char *full_path, t_cmd *cmd, t_env_pack env_pack)
{
	char		*new_pwd;
	// struct stat	buf;

	env_pack = init_env_pack(cmd);
	// printf("full_path: %s\n", full_path);
	if (chdir(full_path) == -1)
	{
		// printf("error: %d\n", errno);
		// stat(full_path, &buf);
		// if (errno == ENOENT && S_ISDIR(buf.st_mode))
		// {
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(cmd->args[0], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(cmd->args[1], 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd(strerror(errno), 2);
			env_pack.original_env = export_original(cmd->original_env, 1);
		// }
		// else if (errno == ENOENT && !S_ISDIR(buf.st_mode))
		// {
			///
			// ft_putstr_fd("cd: error retrieving current directory: ", 2);
			// ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
			// ft_putendl_fd(strerror(ENOENT), 2);
			// env_pack.original_env = export_original(cmd->original_env, 0);
			///
		// }
		// else
		// {
		// 	ft_putstr_fd("bash: ", 2);
		// 	ft_putstr_fd(cmd->args[0], 2);
		// 	ft_putstr_fd(": ", 2);
		// 	ft_putstr_fd(cmd->args[1], 2);
		// 	ft_putstr_fd(": ", 2);
		// 	ft_putendl_fd(strerror(errno), 2);
		// 	env_pack.original_env = export_original(cmd->original_env, 1);
		// }
	}
	else
	{
		new_pwd = getcwd(NULL, 0);
		//protecion
		env_pack.env = custom_export(env_pack.env, "PWD", new_pwd);
		env_pack.original_env = export_original(cmd->original_env, 0);
	}
	return (env_pack);
}

t_env_pack	run_cd(t_cmd *cmd)
{
	char		*old_pwd;
	t_env_pack	env_pack;
	char		*full_path;
	char		*home;

	env_pack = init_env_pack(cmd);
	old_pwd = getcwd(NULL, 0);
	//protecion
	if (!old_pwd && errno == ENOENT)
		old_pwd = value_finder(env_pack.env, "PWD");
	env_pack.env = custom_export(env_pack.env, "OLDPWD", old_pwd);
	home = value_finder(cmd->original_env, "HOME");
	full_path = full_path_finder(old_pwd, cmd->args[1], home);
	env_pack = run_cd_helper(full_path, cmd, env_pack);
	free(full_path);
	return (env_pack);
}
