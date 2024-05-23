/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:56:25 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/23 14:26:28 by nnourine         ###   ########.fr       */
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

char *full_path_finder(char *pwd, char *arg, char *home)
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

t_env_pack	run_cd(t_cmd *cmd)
{
	char		*old_pwd;
	t_env_pack	env_pack;
	char		*full_path;
	char		*new_pwd;
	char		*home;

	env_pack = init_env_pack(cmd);
	old_pwd = getcwd(NULL, 0);
	//protecion if(!old_pwd)
	env_pack.env = custom_export(env_pack.env, "OLDPWD", old_pwd);
	home = value_finder(cmd->original_env, "HOME");
	full_path = full_path_finder(old_pwd, cmd->args[1], home);
	if (chdir(full_path) == -1)
	{
		printf("bash: %s: %s: %s\n",cmd->args[0], cmd->args[1], strerror(errno));
		env_pack.original_env = export_original(cmd->original_env, 1);
	}
	else
	{
		new_pwd = getcwd(NULL, 0);
		//protecion if(!new_pwd)
		env_pack.env = custom_export(env_pack.env, "PWD", new_pwd);
		env_pack.original_env = export_original(cmd->original_env, 0);
	}
	free(full_path);
	return (env_pack);
}
