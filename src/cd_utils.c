/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:16:25 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/19 13:19:45 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	start_with_double_dot(char *arg)
{
	if (!arg)
		return (0);
	if (arg[0] == '.' && arg[1] == '.')
		return (1);
	return (0);
}

char	*path_only_one_double_dot(t_env_pack env_pack)
{
	char	*old_pwd;
	char	*full_path;

	old_pwd = value_finder(env_pack.env, "PWD");
	full_path = sliced_str(old_pwd, 0,
			(ft_strrchr(old_pwd, '/') - old_pwd));
	return (full_path);
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

t_env_pack  del_folder_one_dot(t_env_pack env_pack, t_cmd *cmd)
{
	ft_putstr_fd("cd: error retrieving current directory: ", 2);
	ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
	ft_putendl_fd(strerror(ENOENT), 2);
	env_pack.original_env = export_original(cmd->original_env, 0);
	return (env_pack);
}

t_env_pack  del_folder_else(t_env_pack env_pack, t_cmd *cmd)
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
