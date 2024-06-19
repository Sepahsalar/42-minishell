/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_utils3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:22:42 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/19 12:23:40 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_pid_from_file(int fd)
{
	char	*pid_str;

	pid_str = get_next_line(fd);
	if (!pid_str)
		pid_str = ft_strdup("$$");
	else if (pid_str && ft_strlen(pid_str) > 1)
		pid_str[ft_strlen(pid_str) - 1] = '\0';
	return (pid_str);
}

char	*get_current_pid(t_env *original_env)
{
	char		*raw_line;
	int			fd;
	char		*pid_str;
	t_env_pack	env_pack;
	t_env		*cpy;	

	raw_line = "ps|awk '$4==\"minishell\"'|tail -n 1|awk '{print $1}' >.pid";
	cpy = cpy_env(original_env);
	if (!cpy)
		pid_str = ft_strdup("$$");
	cpy = export_original(cpy, 0);
	if (!cpy)
		pid_str = ft_strdup("$$");
	env_pack.env = cpy;
	env_pack.original_env = cpy;
	execute_all(raw_line, env_pack);
	fd = open(".pid", O_RDONLY);
	pid_str = get_pid_from_file(fd);
	clean_env_list(cpy);
	if (close(fd) == -1)
		exit(1);
	if (unlink(".pid") == -1)
		exit(1);
	return (pid_str);
}
