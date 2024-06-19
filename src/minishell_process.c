/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:00:16 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/19 17:18:05 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	minishell_process(t_env_pack env_pack)
{
	char	*raw_line;

	while (1)
	{
		if (change_mode(WAIT_FOR_COMMAND))
			clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
		raw_line = readline(ANSI_COLOR_GREEN "[ASAL]" ANSI_COLOR_RESET"$ ");
		if (!raw_line)
			process_to_exit(env_pack);
		if (should_execute(raw_line))
		{
			env_pack = export_std_fd(env_pack);
			history_management(env_pack, raw_line);
			env_pack = execute_all(raw_line, env_pack);
			reset_std_fd(env_pack);
		}
		free(raw_line);
	}
}

int	should_execute(char *raw_line)
{
	return (ft_strlen(raw_line) > 0 && !all_space(raw_line));
}

t_env_pack	export_std_fd(t_env_pack env_pack)
{
	char	*itoa;
	int		fd_stdin;
	int		fd_stdout;

	fd_stdin = dup(STDIN_FILENO);
	if (fd_stdin == -1)
		clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
	fd_stdout = dup(STDOUT_FILENO);
	if (fd_stdout == -1)
		clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
	itoa = ft_itoa(fd_stdin);
	if (!itoa)
		clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
	env_pack.original_env = custom_export(env_pack.original_env,
			"fd_stdin", itoa);
	free(itoa);
	itoa = ft_itoa(fd_stdout);
	if (!itoa)
		clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
	env_pack.original_env = custom_export(env_pack.original_env,
			"fd_stdout", itoa);
	free(itoa);
	return (env_pack);
}

void	history_management(t_env_pack env_pack, char *raw_line)
{
	if (save_history(raw_line, value_finder(env_pack.original_env, "root")))
		clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
	rl_clear_history();
	if (load_history(value_finder(env_pack.original_env, "root")))
		clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
}

void	reset_std_fd(t_env_pack env_pack)
{
	int		fd_stdin;
	int		fd_stdout;
	char	*value;

	value = value_finder(env_pack.original_env, "fd_stdin");
	if (value && ft_atoi(value) >= 0)
	{
		fd_stdin = ft_atoi(value);
		if (dup(fd_stdin) == -1)
			clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
		if (close(fd_stdin) == -1)
			clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
	}
	value = value_finder(env_pack.original_env, "fd_stdout");
	if (value && ft_atoi(value) >= 0)
	{
		fd_stdout = ft_atoi(value);
		if (close(STDOUT_FILENO) == -1)
			clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
		if (dup(fd_stdout) == -1)
			clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
		if (close(fd_stdout) == -1)
			clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
	}
}
