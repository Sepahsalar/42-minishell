/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:42:44 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/05 13:01:53 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// 1) error handling on fd operators

// 2) when cd to a directory, it will create a ".history" file
// inside of that directory and it does not load previous commands
// before that directory anymore and it does not load from the one
// that already exists in the repo

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
	// bash-3.2$ cd mi
	// bash: cd: mi: No such file or directory
// ex: ASAL
	// [ASAL]$ pwd
	// /Users/asohrabi/github/42-minishell/mi
	// [ASAL]$ ls
	// [ASAL]$ ls -la
	// total 8
	// drwxr-xr-x   3 asohrabi  2020  102 Jun  5 12:28 .
	// drwxr-xr-x  16 asohrabi  2020  544 Jun  5 12:28 ..
	// -rw-r--r--   1 asohrabi  2020   27 Jun  5 12:29 .history
	// [ASAL]$ pwd
	// /Users/asohrabi/github/42-minishell/mi
	// [ASAL]$ cd mi
	// bash: cd: mi: Bad address
	// [ASAL]$ cd .
	// bash: cd: .: Bad address
	// [ASAL]$ pwd
	//             --> Empty line
	// also $OLDPWD returns nothing (it is also deleted from export)

t_env_pack	env_pack_at_start(char **envp, int fd_stdin, int fd_stdout)
{
	t_env_pack	env_pack;
	char		*pid;
	t_env		*original_env;

	env_pack.env = set_start(fill_env_list(envp));
	pid = get_current_pid(env_pack.env);
	dup(fd_stdin);
	close(STDOUT_FILENO);
	dup(fd_stdout);
	original_env = fill_env_list(envp);
	original_env = custom_export(original_env,
			ft_strdup("pid"), ft_strdup(pid));
	original_env = export_original(original_env, 0);
	env_pack.original_env = original_env;
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
	close(fd_stdin);
	close(fd_stdout);
	return (0);
}
