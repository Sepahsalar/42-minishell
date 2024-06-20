/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_utils3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:22:42 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/20 13:13:44 by asohrabi         ###   ########.fr       */
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

// char	*get_current_pid(t_env *original_env)
// {
// 	char		*raw_line;
// 	int			fd;
// 	char		*pid_str;
// 	t_env_pack	env_pack;
// 	t_env		*cpy;
// 	int			fd_stderr;
// 	int			fd_pid_error;

// 	fd_stderr = dup(STDERR_FILENO);
// 	if (fd_stderr == -1)
// 		pid_str = ft_strdup("$$");
// 	fd_pid_error = open(".pid2", O_RDWR | O_CREAT | O_TRUNC, 0644);
// 	if (fd_pid_error == -1)
// 		pid_str = ft_strdup("$$");
// 	if (dup2(fd_pid_error, STDERR_FILENO) == -1)
// 		pid_str = ft_strdup("$$");
// 	raw_line = "ps|awk '$4==\"minishell\"'|tail -n 1|awk '{print $1}' >.pid";
// 	cpy = cpy_env(original_env);
// 	if (!cpy)
// 		pid_str = ft_strdup("$$");
// 	cpy = export_original(cpy, 0);
// 	if (!cpy)
// 		pid_str = ft_strdup("$$");
// 	env_pack.env = cpy;
// 	env_pack.original_env = cpy;
// 	execute_all(raw_line, env_pack);
// 	if (close(STDERR_FILENO) == -1)
// 		pid_str = ft_strdup("$$");
// 	if (dup(fd_stderr) == -1)
// 		pid_str = ft_strdup("$$");
// 	if (close(fd_stderr) == -1)
// 		pid_str = ft_strdup("$$");
// 	fd = open(".pid", O_RDONLY);
// 	pid_str = get_pid_from_file(fd);
// 	clean_env_list(cpy);
// 	if (close(fd) == -1)
// 		pid_str = ft_strdup("$$");
// 	if (unlink(".pid2") == -1)
// 		pid_str = ft_strdup("$$");
// 	if (unlink(".pid") == -1)
// 		pid_str = ft_strdup("$$");
// 	return (pid_str);
// }

static char	*create_pid_file(t_env *cpy)
{
	int		fd;
	char	*pid_str;

	fd = open(".pid", O_RDONLY);
	pid_str = get_pid_from_file(fd);
	clean_env_list(cpy);
	close(fd);
	unlink(".pid2");
	unlink(".pid");
	return (pid_str);
}

static t_env	*extract_pid(t_env *original_env)
{
	char		*line;
	t_env_pack	env_pack;
	t_env		*cpy;

	line = "ps|awk '$4==\"minishell\"'|tail -n 1|awk '{print $1}' >.pid";
	cpy = cpy_env(original_env);
	cpy = export_original(cpy, 0);
	env_pack.env = cpy;
	env_pack.original_env = cpy;
	execute_all(line, env_pack);
	return (cpy);
}

char	*get_current_pid(t_env *original_env)
{
	char	*pid_str;
	t_env	*cpy;
	int		fd_stderr;
	int		fd_pid_error;

	fd_stderr = dup(STDERR_FILENO);
	fd_pid_error = open(".pid2", O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup2(fd_pid_error, STDERR_FILENO);
	cpy = extract_pid(original_env);
	close(STDERR_FILENO);
	dup(fd_stderr);
	close(fd_stderr);
	pid_str = create_pid_file(cpy);
	return (pid_str);
}
