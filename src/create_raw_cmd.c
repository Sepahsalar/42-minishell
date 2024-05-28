/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_raw_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:06:38 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/28 18:34:52 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**create_raw_cmd(const char *input)
{
	char	**raw_cmd;
	// int index = 0;

	raw_cmd = split_pipex_pipe(input);
	// while(raw_cmd[index])
	// {
	// 	printf("%s\n", raw_cmd[index]);
	// 	index++;
	// }
	if (!raw_cmd)
		master_clean(0, 0, 0, EXIT_FAILURE);
	return (raw_cmd);
}

// int	cmd_counter_error(const char *input)
// {
// 	char	**raw_cmd;
// 	int		count;

// 	raw_cmd = ft_split(input, '|');
// 	count = char_2d_count(raw_cmd);
// 	clean_2d_char(raw_cmd);
// 	if (input[ft_strlen(input) - 1] != '|')
// 		return (count);
// 	else
// 		return (count + 1);
// }
