/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:42:44 by nnourine          #+#    #+#             */
/*   Updated: 2024/04/18 14:59:04 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv)
{
	t_cmd	*cmd;
	char	**raw_cmd;
	int		cmd_count;

	(void)argc;
	raw_cmd = ft_create_raw_cmd(argv[1]);
	if (!raw_cmd)
		return (EXIT_FAILURE);
	cmd_count = ft_cmd_count(raw_cmd);
	cmd = ft_create_cmd_list(cmd_count);
	if (ft_fill_raw_cmd_list(&cmd, raw_cmd))
		return (EXIT_FAILURE);
	ft_clean_2d_char(raw_cmd);
	ft_clean_cmd_list(cmd);
	return (0);
}
