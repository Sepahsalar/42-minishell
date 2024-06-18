/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:42:44 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/18 14:42:23 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile int	g_signal;

// test this in bash macOS:
// 1) > 2>>
// 2) > 2a>> temp

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

t_env_pack	env_pack_at_start(char **envp, int fd_stdin, int fd_stdout, char *root)
{
	t_env_pack	env_pack;
	char		*pid;
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
	pid = get_current_pid(env_pack.env);
	if (!pid)
		clean_all(original_env, env, root, NULL);
	if (dup(fd_stdin) == -1)
		clean_all(original_env, env, root, pid);
	close(STDOUT_FILENO);
	if (dup(fd_stdout) == -1)
		clean_all(original_env, env, root, pid);
	close(fd_stdin);
	close(fd_stdout);
	original_env = custom_export(original_env, "fd_stdin", "-2");
	original_env = custom_export(original_env, "fd_stdout", "-2");
	original_env = custom_export(original_env, "root", root);
	original_env = custom_export(original_env, "pid", pid);
	free(root);
	free(pid);
	original_env = export_original(original_env, 0);
	env_pack.original_env = original_env;
	return (env_pack);
}

void	minishell_process(t_env_pack env_pack)
{
	char	*raw_line;
	int		fd_stdin;
	int		fd_stdout;
	char	*itoa;

	while (1)
	{
		if (change_mode(WAIT_FOR_COMMAND))
			clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
		raw_line = readline(ANSI_COLOR_GREEN "[ASAL]" ANSI_COLOR_RESET"$ ");
		if (!raw_line)
		{
			clean_env_list(env_pack.env);
			run_exit_eof(env_pack.original_env);
		}
		if (ft_strlen(raw_line) > 0 && !all_space(raw_line))
		{
			fd_stdin = dup(STDIN_FILENO);
			if (fd_stdin == -1)
			    clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
			itoa = ft_itoa(fd_stdin);
			if (!itoa)
			    clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
			env_pack.original_env = custom_export(env_pack.original_env, "fd_stdin", itoa);
			free(itoa);
			fd_stdout = dup(STDOUT_FILENO);
			if (fd_stdout == -1)
			    clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
			itoa = ft_itoa(fd_stdout);
			if (!itoa)
                clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
			env_pack.original_env = custom_export(env_pack.original_env, "fd_stdout", itoa);
			free(itoa);
			if (save_history(raw_line, value_finder(env_pack.original_env, "root")))
                clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
			rl_clear_history();
			if (load_history(value_finder(env_pack.original_env, "root")))
                clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
			env_pack = execute_all(raw_line, env_pack);
			if (dup(fd_stdin) == -1)
			    clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
			close(STDOUT_FILENO);
			if (dup(fd_stdout) == -1)
			    clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
			close(fd_stdin);
			close(fd_stdout);
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
