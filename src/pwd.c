/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:26:11 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/05 13:00:25 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env_pack	run_pwd(t_cmd *cmd)
{
	t_env_pack	env_pack;
	char		*path;

	path = NULL;
	env_pack = init_env_pack(cmd);
	path = getcwd(NULL, 0);
	if (path)
		ft_putendl_fd(path, 1);
	else if (!path && errno == 2)
		ft_putendl_fd(value_finder(env_pack.env, "PWD"), 1);
	//maybe protection against failure
	free(path);
	export_original(env_pack.original_env, 0);
	return (env_pack);
}
