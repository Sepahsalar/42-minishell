/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:56:25 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/23 09:18:27 by nnourine         ###   ########.fr       */
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

char *handle_sd(char *arg)
{
	if (arg[0] == '.' && arg[1] == '/')
		return (arg + 2);
	else if (arg[0] == '.')
	    return (arg + 1);
	else
		return (arg);
}

char *full_path_finder(char *pwd, char *arg, char *home)
{
	char	*temp1;
	char	*temp2;

	if (arg[0] == '~')
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

// t_dot	init_dot(char *old_pwd, char *arg)
// {
// 	t_dot	dot;

// 	dot.old_pwd = old_pwd;
// 	dot.arg = arg;
// 	dot.i_arg = 0;
// 	dot.i_old = (int)ft_strlen(old_pwd) - 1;
// 	return (dot);
// }

// t_dot handle_dot_once(t_dot dot)
// {
// 	if (dot.arg[dot.i_arg] && dot.arg[dot.i_arg] == '.' && dot.arg[dot.i_arg + 1] == '/')
// 		dot.i_arg += 2;
// 	else if (dot.arg[dot.i_arg] && dot.arg[dot.i_arg] == '.' && dot.arg[dot.i_arg + 1] && dot.arg[dot.i_arg + 1] == '.' && dot.arg[dot.i_arg + 2] == '/')
// 	{
// 		dot.i_arg += 3;
// 		while (dot.old_pwd[dot.i_old] != '/')
// 		    dot.i_old--;
// 		dot.i_old--;
// 	}
// 	return (dot);
// }

// t_dot handle_dot(t_dot dot)
// {
// 	while ((dot.arg[dot.i_arg] && dot.arg[dot.i_arg] == '.'
// 			&& dot.arg[dot.i_arg + 1] == '/')
// 		|| (dot.arg[dot.i_arg] && dot.arg[dot.i_arg] == '.'
// 			&& dot.arg[dot.i_arg + 1] && dot.arg[dot.i_arg + 1] == '.'
// 			&& dot.arg[dot.i_arg + 2] == '/'))
// 		dot = handle_dot_once(dot);
// 	return (dot);
// }

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

// t_env_pack run_cd(t_cmd *cmd)
// {
// 	char		*old_pwd;
// 	t_env_pack	env_pack;
// 	char		*full_path;
// 	t_dot		dot;
// 	char		*new_arg;
// 	char		*new_pwd;
// 	char		*home;
// 	int			index;

// 	env_pack = init_env_pack(cmd);
// 	old_pwd = getcwd(NULL, 0);
// 	//protecion if(!old_pwd)
// 	env_pack.env = custom_export(env_pack.env, "OLDPWD", old_pwd);
// 	if (same(cmd->args[1], "..") || same(cmd->args[1], "."))
// 	{
// 		env_pack.original_env = export_original(cmd->original_env, 0);
// 		if (same(cmd->args[1], "."))
// 			return (env_pack);
// 		else
// 		{
// 			index = ft_strlen(old_pwd) - 1;
// 			while (old_pwd[index] != '/')
// 				index--;
// 			index--;
// 			new_pwd = sliced_str(old_pwd, 0, index);
// 			full_path = ft_strdup(new_pwd);
// 			free(new_pwd);
// 		}
// 	}
// 	else
// 	{
// 		dot = init_dot(old_pwd, cmd->args[1]);
// 		dot = handle_dot(dot);
// 		printf("new_arg: %s and index pwd is : %d\n", (dot.arg + dot.i_arg), dot.i_old);
// 		new_arg = sliced_str(dot.arg, dot.i_arg, (int)ft_strlen(dot.arg) - 1);
// 		new_pwd = sliced_str(dot.old_pwd, 0, dot.i_old);
// 		home = value_finder(cmd->original_env, "HOME");
// 		full_path = full_path_finder(new_pwd, new_arg, env_pack.env->value);
// 		printf("full_path: %s\n", full_path);
// 		// free(home);
// 		// free(new_pwd);
// 		// free(new_arg);
// 	}
// 	if (chdir(full_path) == -1)
// 	{
// 		perror("bash");
// 		env_pack.original_env = export_original(cmd->original_env, 1);
// 	}
// 	else
// 	{
// 		env_pack.env = custom_export(env_pack.env, "PWD", full_path);
// 		env_pack.original_env = export_original(cmd->original_env, 0);
// 	}
// 	return (env_pack);
// }

t_env_pack run_cd(t_cmd *cmd)
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
	full_path = full_path_finder(old_pwd, cmd->args[1], env_pack.env->value);
	if (chdir(full_path) == -1)
	{
		perror("bash");
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
