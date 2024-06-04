/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:12:42 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/04 19:19:35 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	run_execve(char *cmd_address, char **cmd_args, char **cmd_env)
{
	if (execve(cmd_address, cmd_args, cmd_env) == -1)
	{
		clean_2d_char(cmd_args);
		clean_2d_char(cmd_env);
		if (same (strerror(errno), "Exec format error"))
		{
			if (!check_accessibility(cmd_address, 'R'))
			{
				ft_putstr_fd("bash: ", 2);
				ft_putstr_fd(cmd_address, 2);
				free(cmd_address);
				ft_putendl_fd(": Permission denied", 2);
				exit(126);
			}
			free(cmd_address);
			exit(0);
		}
		free(cmd_address);
		perror("bash");
		exit(1);
	}
}
