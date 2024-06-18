/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:56:25 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/18 19:20:48 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*custom_export(t_env *env, char *key, char *value)
{
	t_env	*temp;
	char	*temp_key;
	char	*temp_value;

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
		if (!temp->value)
			clean_all(env, NULL, NULL, NULL);
	}
	else
	{
		temp_key = ft_strdup(key);
		temp_value = ft_strdup(value);
		if (!temp_key || !temp_value)
			clean_all(env, NULL, temp_key, temp_value);
		add_node_front(&env, temp_key, temp_value);
		if (!env)
			clean_all(env, NULL, temp_key, temp_value);
	}
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
		if (!temp1)
			return (NULL);
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
	return (env_pack);
}

int	start_with_double_dot(char *arg)
{
	if (!arg || ft_strlen(arg) <= 2)
		return (0);
	if (arg[0] == '.' && arg[1] == '.')
		return (1);
	return (0);
}

char	*path_start_with_double_dot(t_cmd *cmd, t_env_pack env_pack)
{
	char	*old_pwd;
	char	*part_one;
	char	*part_two;
	char	*full_path;

	old_pwd = value_finder(env_pack.env, "PWD");
	part_one = sliced_str(old_pwd, 0,
			(ft_strrchr(old_pwd, '/') - old_pwd));
	if (!part_one)
		return (NULL);
	part_two = sliced_str(cmd->args[1], 2, ft_strlen(cmd->args[1]));
	if (!part_two)
	{
		free(part_one);
		return (NULL);
	}
	full_path = ft_strjoin(part_one, part_two);
	free(part_one);
	free(part_two);
	return (full_path);
}

t_env_pack	run_cd(t_cmd *cmd)
{
	char		*old_pwd;
	t_env_pack	env_pack;
	char		*full_path;
	char		*home;

	full_path = NULL;
	env_pack = init_env_pack(cmd);
	// if (cmd->args[2])
	// {
    //     ft_putendl_fd("bash: cd: too many arguments", 2);
    //     env_pack.original_env = export_original(cmd->original_env, 1);
    //     return (env_pack);
    // }
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		if (same(cmd->args[1], ".") && errno == ENOENT)
		{
			ft_putstr_fd("cd: error retrieving current directory: ", 2);
			ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
			ft_putendl_fd(strerror(ENOENT), 2);
			env_pack.original_env = export_original(cmd->original_env, 0);
			return (env_pack);
		}
		else if (cmd->args[1] && same(cmd->args[1], ".."))
		{
			old_pwd = value_finder(env_pack.env, "PWD");
			full_path = sliced_str(old_pwd, 0,
					(ft_strrchr(old_pwd, '/') - old_pwd));
		}
		else if (start_with_double_dot(cmd->args[1]))
			full_path = path_start_with_double_dot(cmd, env_pack);
		else if (cmd->args[1] == NULL)
			full_path = ft_strdup(value_finder(cmd->original_env, "HOME"));
		else
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(cmd->args[0], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(cmd->args[1], 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd(strerror(errno), 2);
			env_pack.original_env = export_original(cmd->original_env, 1);
			return (env_pack);
		}
		//old_pwd = ft_strdup(value_finder(env_pack.env, "PWD"));
	}
	else
	{
		env_pack.env = custom_export(env_pack.env, "OLDPWD", old_pwd);
		home = value_finder(cmd->original_env, "HOME");
		full_path = full_path_finder(old_pwd, cmd->args[1], home);
		free(old_pwd);
	}
	if (!full_path)
		master_clean(NULL, cmd, EXIT_FAILURE);
	env_pack = run_cd_helper(full_path, cmd, env_pack);
	free(full_path);
	return (env_pack);
}
