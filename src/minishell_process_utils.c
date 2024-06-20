/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_process_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:17:07 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/20 12:41:50 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	reset_std(t_env_pack env_pack, int fd_std, char *key)
{
	int		fd;
	char	*value;

	value = value_finder(env_pack.original_env, key);
	if (value && ft_atoi(value) >= 0)
	{
		fd = ft_atoi(value);
		if (fd_std != STDIN_FILENO)
		{
			if (close(fd_std) == -1)
				clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
		}
		if (dup(fd) == -1)
			clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
		if (close(fd) == -1)
			clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
	}
}

void	reset_std_fd(t_env_pack env_pack)
{
	reset_std(env_pack, STDIN_FILENO, "fd_stdin");
	reset_std(env_pack, STDOUT_FILENO, "fd_stdout");
	reset_std(env_pack, STDERR_FILENO, "fd_stderr");
}
