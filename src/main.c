/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:42:44 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/19 16:13:46 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile int	g_signal;

// test this in bash macOS:
// 1) > 2>>
// 2) > 2a>> temp
// 3) < 2a <<
// 4) > & not_handling or unexpected token
// 5) || has a leak                            done
// 6) << hi cat -> has error                   done
 

// search for all voids in functions ("(void)...") and delete them

// delete .history in makefile

// norminette:
// 1) cd ---------------------------- medium->nima done
// 2) expand_dollar_utils.c --------- short        done
// 3) export_utils2.c --------------- short        done
// 4) export.c ---------------------- short        done
// 5) fd_heredoc_utils.c------------- short        done
// 6) fill_env_list.c---------------- short        done
// 7) fill_files_helper_all.c-------- short        done
// 8) fill_files_helper.c------------ short        done
// 9) find_cmd_address_utils.c------- short        done
//10) handle_dollar.c --------------- short        done
//11) handle_history.c -------------- short        done
//12) handle_quote.c ---------------- short ->nima done
//13) init_temp_env.c --------------- short ->nima done
//14) main.c ------------------------ long  ->nima done
//15) master_clean.c ---------------- short ->nima done
//16) pipex_error_handling_heredoc.c- short ->nima done
//17) pipex_error_handling_utils.c--- short ->nima done
//18) pipex_error_handling_utils2.c-- short ->nima done
//19) recreate_2d_env.c ------------- short ->nima done
//20) utility4.c -------------------- medium->nima done
//21) export_utils.c ---------------- short ->nima done

void	clean_all(t_env *env1, t_env *env2, char *str1, char *str2)
{
	if (env1)
		clean_env_list(env1);
	if (env2)
		clean_env_list(env2);
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		exit(1);
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
	    exit(1);
	if (change_mode(RUNNING_COMMAND))
		exit(1);
	exit(1);
}

t_env *env_pack_at_start_pid(t_env *original_env, t_env *env, int fd_stdin, int fd_stdout)
{
	char		*pid;
	
	
	pid = get_current_pid(env);
	if (!pid)
		clean_all(original_env, env, NULL, NULL);
	if (dup(fd_stdin) == -1)
		clean_all(original_env, env, pid, NULL);
	if (close(STDOUT_FILENO) == -1)
		clean_all(original_env, env, pid, NULL);
	if (dup(fd_stdout) == -1)
		clean_all(original_env, env, pid, NULL);
	if (close(fd_stdin) == -1)
		clean_all(original_env, env, pid, NULL);
	if (close(fd_stdout) == -1)
		clean_all(original_env, env, pid, NULL);
	original_env = custom_export(original_env, "pid", pid);
	free(pid);
	return (original_env);
}

t_env_pack	env_pack_at_start(char **envp, int fd_stdin, int fd_stdout, char *root)
{
	t_env_pack	env_pack;
	t_env		*original_env;
	t_env		*env;

	original_env = fill_env_list(envp);
	env = fill_env_list(envp);
	if (!original_env || !env)
		clean_all(original_env, env, root, NULL);
	env = set_start(env);
	if (!env)
		clean_all(original_env, env, root, NULL);
	env_pack.env = env;
	original_env = custom_export(original_env, "fd_stdin", "-2");
	original_env = custom_export(original_env, "fd_stdout", "-2");
	original_env = custom_export(original_env, "root", root);
	free(root);
	original_env = env_pack_at_start_pid(original_env, env, fd_stdin, fd_stdout);
	original_env = export_original(original_env, 0);
	env_pack.original_env = original_env;
	return (env_pack);
}

t_env_pack export_std_fd(t_env_pack env_pack)
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
	env_pack.original_env = custom_export(env_pack.original_env, "fd_stdin", itoa);
	free(itoa);
	itoa = ft_itoa(fd_stdout);
	if (!itoa)
		clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
	env_pack.original_env = custom_export(env_pack.original_env, "fd_stdout", itoa);
	free(itoa);
	return (env_pack);
}

void reset_std_fd(t_env_pack env_pack)
{
	int fd_stdin;
	int fd_stdout;
	char *value;

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

void	process_to_exit(t_env_pack env_pack)
{
	clean_env_list(env_pack.env);
    run_exit_eof(env_pack.original_env);
}

int should_execute(char *raw_line)
{
	return (ft_strlen(raw_line) > 0 && !all_space(raw_line));
}

void history_management(t_env_pack env_pack, char *raw_line)
{
	if (save_history(raw_line, value_finder(env_pack.original_env, "root")))
		clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
	rl_clear_history();
	if (load_history(value_finder(env_pack.original_env, "root")))
		clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
}

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

int	main(int argc, char **argv, char **envp)
{
	int			fd_stdin;
	int			fd_stdout;
	t_env_pack	env_pack;
	char		*root;

	(void)argc;
	(void)argv;
	root = getcwd(NULL, 0);
	if (!root)
		return (1);
	fd_stdin = dup(STDIN_FILENO);
	fd_stdout = dup(STDOUT_FILENO);
	if (fd_stdin == -1 || fd_stdout == -1)
	{
		free(root);
		return (1);
	}
	env_pack = env_pack_at_start(envp, fd_stdin, fd_stdout, root);
	if (load_history(value_finder(env_pack.original_env, "root")))
	    clean_all(env_pack.original_env, env_pack.env, root, NULL);
	minishell_process(env_pack);
	free(root);
	return (0);
}
