/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_raw_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:06:38 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/18 13:40:09 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**create_raw_cmd(const char *input)
{
	char	**raw_cmd;

	raw_cmd = split_pipex_pipe(input);
	if (!raw_cmd)
		return (NULL);
	return (raw_cmd);
}
