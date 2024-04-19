/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:42:44 by nnourine          #+#    #+#             */
/*   Updated: 2024/04/19 12:10:13 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// remember to merge the libft in lib and in pipex

int	main(int argc, char **argv, char **envp)
{
	char	**raw_cmd;
	t_env	*env;
	t_cmd	*cmd;

	(void)argc;
	raw_cmd = ft_create_raw_cmd(argv[1]);
	env = ft_fill_env_list(envp, raw_cmd);
	cmd = ft_fill_cmd_list(raw_cmd, env);
	ft_master_clean(raw_cmd, env, cmd, EXIT_SUCCESS);
}
