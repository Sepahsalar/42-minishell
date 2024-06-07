/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:42:44 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/07 11:27:17 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// 1) error handling on fd operators

t_env_pack	env_pack_at_start(char **envp, int fd_stdin, int fd_stdout)
{
	t_env_pack	env_pack;
	char		*pid;
	t_env		*original_env;
	t_env		*env;

	original_env = fill_env_list(envp);
	env = fill_env_list(envp);
	env = set_start(env);
	env_pack.env = env;
	pid = get_current_pid(env_pack.env);
	dup(fd_stdin);
	close(STDOUT_FILENO);
	dup(fd_stdout);
	original_env = custom_export(original_env, "pid", pid);
	free(pid);
	original_env = export_original(original_env, 0);
	env_pack.original_env = original_env;
	return (env_pack);
}

void	minishell_process(t_env_pack env_pack, int fd_stdin,
				int fd_stdout, char *root)
{
	char		*raw_line;
	t_signal	old_signal;

	old_signal = apply_custom_signal_handler();

	while (1)
	{
		change_mode(WAIT_FOR_COMMAND);
		raw_line = readline(ANSI_COLOR_GREEN "[ASAL]" ANSI_COLOR_RESET"$ ");
		if (!raw_line)
		{
			sigaction(SIGINT, &old_signal.sig_int, NULL);
			sigaction(SIGQUIT, &old_signal.sig_quit, NULL);
			clean_env_list(env_pack.env);
			free(root);
			run_exit_eof(env_pack.original_env, fd_stdin, fd_stdout);
		}
		if (same(raw_line, "checkleaks"))
			system("leaks -q minishell"); //remember to delete it
		if (ft_strlen(raw_line) > 0 && !all_space(raw_line))
		{
			save_history(raw_line, root);
			rl_clear_history();
			load_history(root);
			env_pack = execute_all(raw_line, env_pack);
			close(STDIN_FILENO);
			dup(fd_stdin);
			close(STDOUT_FILENO);
			dup(fd_stdout);
		}
		free(raw_line);
	}
	clean_env_list(env_pack.original_env);
	clean_env_list(env_pack.env);
}

int	main(int argc, char **argv, char **envp)
{
	int			fd_stdin;
	int			fd_stdout;
	t_env_pack	env_pack;
	char		*root;

	root = getcwd(NULL, 0);
	(void)argc;
	(void)argv;
	fd_stdin = dup(STDIN_FILENO);
	fd_stdout = dup(STDOUT_FILENO);
	env_pack = env_pack_at_start(envp, fd_stdin, fd_stdout);
	load_history(root);
	// apply_custom_signal_handler();
	minishell_process(env_pack, fd_stdin, fd_stdout, root);
	//we messed up with system signals, we should fix it
	close(fd_stdin);
	close(fd_stdout);
	free(root);
	return (0);
}
