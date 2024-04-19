/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:42:44 by nnourine          #+#    #+#             */
/*   Updated: 2024/04/19 09:40:43 by nnourine         ###   ########.fr       */
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
		return (ft_master_clean(0, 0, EXIT_FAILURE));
	cmd_count = ft_cmd_count(raw_cmd);
	cmd = ft_create_cmd_list(cmd_count);
	if (!cmd)
		return (ft_master_clean(raw_cmd, 0, EXIT_FAILURE));
	ft_fill_index_cmd_list(&cmd);
	if (ft_fill_raw_cmd_list(&cmd, raw_cmd))
		return (ft_master_clean(raw_cmd, cmd, EXIT_FAILURE));
	if (ft_fill_heredoc_cmd_list(&cmd))
		return (ft_master_clean(raw_cmd, cmd, EXIT_FAILURE));
	return (ft_master_clean(raw_cmd, cmd, EXIT_SUCCESS));
}
