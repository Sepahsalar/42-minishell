/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:42:44 by nnourine          #+#    #+#             */
/*   Updated: 2024/04/22 16:06:21 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	**raw_cmd;
	t_env	*env;
	t_cmd	*cmd;
	char	*a[6];

	(void)argc;
	raw_cmd = ft_create_raw_cmd(argv[1]);
	env = ft_fill_env_list(envp, raw_cmd);
	cmd = ft_fill_cmd_list(raw_cmd, env);
	a[0] = 0;
	a[1] = cmd->input->raw;
	a[2] = cmd->current;
	a[3] = cmd->next->current;
	a[4] = cmd->next->output_trunc->raw;
	a[5] = NULL;
	pipex_master(5, a, envp);
	ft_master_clean(raw_cmd, env, cmd, EXIT_SUCCESS);
}
