/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:49:01 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/23 09:50:26 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env_pack	run_exit(t_cmd *cmd)
{
	t_env_pack	env_pack;

	env_pack = init_env_pack(cmd);
	return (env_pack);
}
