/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:00:16 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/20 11:46:45 by nnourine         ###   ########.fr       */
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

t_env_pack	export_std_fd_helper(t_env_pack env_pack, int fd_std, char *key)
{
	char	*itoa;
	int		fd;

	fd = dup(fd_std);
	if (fd == -1)
		clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
	itoa = ft_itoa(fd);
	if (!itoa)
		clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
	env_pack.original_env = custom_export(env_pack.original_env,
			key, itoa);
	free(itoa);
	return (env_pack);
}

t_env_pack	export_std_fd(t_env_pack env_pack)
{
	env_pack = export_std_fd_helper(env_pack, STDIN_FILENO, "fd_stdin");
	env_pack = export_std_fd_helper(env_pack, STDOUT_FILENO, "fd_stdout");
	env_pack = export_std_fd_helper(env_pack, STDERR_FILENO, "fd_stderr");
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
