/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:42:44 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/05 16:00:18 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// 1) error handling on fd operators

// 2) when cd to a directory, it will create a ".history" file
// inside of that directory and it does not load previous commands
// before that directory anymore and it does not load from the one
// that already exists in the repo

// also when cd to a directory, OLDPWD becomes nothing
// and it is not also in export

// 2) check cd with file name with too many characters

// also check if you delete a directory from a terminal,
// which you were inside of it from other terminals,
// what should "cd ." builtin do?
// ex: bash
	// bash-3.2$ ls -la
	// total 0
	// drwxr-xr-x   2 asohrabi  2020   68 Jun  5 12:26 .
	// drwxr-xr-x  13 asohrabi  2020  442 Jun  5 12:27 ..
	// bash-3.2$ cd .
	// cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
	// bash-3.2$ pwd
	// /Users/asohrabi/github/42-minishell/mi/.

// ex: ASAL
	// [ASAL]$ ls -la
	// total 8
	// drwxr-xr-x   3 asohrabi  2020  102 Jun  5 12:28 .
	// drwxr-xr-x  16 asohrabi  2020  544 Jun  5 12:28 ..
	// -rw-r--r--   1 asohrabi  2020   27 Jun  5 12:29 .history
	// [ASAL]$ cd .
	// bash: cd: .: No such file or directory
	// also $OLDPWD returns nothing

t_env_pack	env_pack_at_start(char **envp, int fd_stdin, int fd_stdout)
{
	t_env_pack	env_pack;
	char		*pid;
	char		*temp;
	char		*temp_pid;
	t_env		*original_env;

	original_env = fill_env_list(envp);
	env_pack.env = set_start(original_env);
	pid = get_current_pid(env_pack.env);
	dup(fd_stdin);
	close(STDOUT_FILENO);
	dup(fd_stdout);
	// original_env = fill_env_list(envp);
	temp = ft_strdup("pid");
	temp_pid = ft_strdup(pid);
	free(pid);
	original_env = custom_export(original_env, temp, temp_pid);
	free(temp);
	free(temp_pid);
	original_env = export_original(original_env, 0);
	env_pack.original_env = original_env;
	// clean_env_list(original_env);
	return (env_pack);
}

void	minishell_process(t_env_pack env_pack, int fd_stdin, int fd_stdout)
{
	char	*raw_line;

	while (1)
	{
		change_mode(WAIT_FOR_COMMAND);
		raw_line = readline(ANSI_COLOR_GREEN "[ASAL]" ANSI_COLOR_RESET"$ ");
		if (!raw_line)
			run_exit_eof(env_pack.original_env, fd_stdin, fd_stdout);
		if (same(raw_line, "checkleaks"))
			system("leaks -q minishell"); //remember to delete it
		if (ft_strlen(raw_line) > 0 && !all_space(raw_line))
		{
			save_history(raw_line);
			rl_clear_history();
			load_history();
			env_pack = execute_all(raw_line, env_pack);
			close(STDIN_FILENO);
			dup(fd_stdin);
			close(STDOUT_FILENO);
			dup(fd_stdout);
		}
		free(raw_line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int			fd_stdin;
	int			fd_stdout;
	t_env_pack	env_pack;

	(void)argc;
	(void)argv;
	fd_stdin = dup(STDIN_FILENO);
	fd_stdout = dup(STDOUT_FILENO);
	env_pack = env_pack_at_start(envp, fd_stdin, fd_stdout);
	load_history();
	apply_custom_signal_handler();
	minishell_process(env_pack, fd_stdin, fd_stdout);
	// is there a need to apply the original signal handler here??
	// and int the exit_eof_or any other exit
	// system("leaks minishell");
	close(fd_stdin);
	close(fd_stdout);
	// system("exit");
	// system("leaks minishell");
	return (0);
}
