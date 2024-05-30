/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:11:43 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/30 12:20:54 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env_pack	run_echo(t_cmd *cmd)
{
	t_env_pack	env_pack;
	char		**arg;
	int			index;
	char		c;

	env_pack = init_env_pack(cmd);
	arg = cmd->args;
	index = 1;
	c = '\n';
	if (same(arg[1], "-n"))
	{
		index = 2;
		c = '\0';
	}
	while (arg[index])
	{
		// printf("%s", arg[index]);
		ft_putstr_fd(arg[index], 1);
		if (arg[index + 1])
			// printf(" ");
			ft_putstr_fd(" ", 1);
		index++;
	}
	// printf("%c", c);
	ft_putchar_fd(c, 1);
	env_pack.original_env = export_original(cmd->original_env, 0);
	return (env_pack);
}
