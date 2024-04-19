/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:27:08 by nnourine          #+#    #+#             */
/*   Updated: 2024/04/19 09:38:07 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_master_clean(char **raw_cmd, t_cmd *cmd, int return_value)
{
	if (raw_cmd)
		ft_clean_2d_char(raw_cmd);
	if (cmd)
		ft_clean_cmd_list(cmd);
	return (return_value);
}
