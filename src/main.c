/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:42:44 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/05 10:43:11 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Norminette:
// 1) error_handling-----------big     --done
// 2) expand dollar------------big     --done
// 3) fd heredoc---------------big     --done
// 4) ft remove----------------little  --done
// 5) fill cmd list------------little  --done
// 6) find cmd address---------big     --done
// 7) fill dollar list---------little  --done
// 8) fill files helper--------big     --done
// 9) recreate 2d env----------little  --done
//10) split pipex utils--------little  --done
//11) split pipex--------------little  --done
//12) utility 1----------------little  --done
//13) utility 4----------------little  --done

// 1) check these out in bash: -- done
// << USER cat
// << $USER cat
// also check if one of the line contain $PATH (it should be expanded)

// 2) check builtins with capital letters like CD .. --done

// 3) error handling on fd operators

// 4) check cd with file name with too many characters
// also check if you delete a directory from a terminal,
// which you were inside of it from other terminals,
// what should "cd" builtin do?

t_env_pack	execute_all(char *raw_line, t_env_pack env_pack)
{
	t_error		error;

	error = find_error(raw_line);
	if (error.error)
		return (error_actions(env_pack, error, raw_line));
	return (execute_actions(raw_line, env_pack));
}

void	sig_handler(int sig)
{
	if (sig == SIGINT && g_signal == RUNNING_COMMAND)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", STDIN_FILENO);
	}
	else if (sig == SIGINT && g_signal == WAIT_FOR_COMMAND)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", STDIN_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGINT && g_signal == HEREDOC)
	{
		ioctl(0, TIOCSTI, "\n");
		printf("\033[1A");
		g_signal = HEREDOC_INTERRUPTED;
	}
}

void	load_history(void)
{
	int		fd_history;
	char	*line;
	char	*temp;

	fd_history = open(".history", O_RDWR | O_CREAT | O_APPEND, 0644);
	line = get_next_line(fd_history);
	if (line)
	{
		temp = line;
		line = ft_strtrim(line, "\n");
		if (temp)
			free(temp);
		while (line)
		{
			add_history(line);
			free(line);
			line = get_next_line(fd_history);
			temp = line;
			line = ft_strtrim(line, "\n");
			if (temp)
				free(temp);
		}
	}
	close(fd_history);
}

void	save_history(char *raw_line)
{
	int	fd_history;

	fd_history = open(".history", O_RDWR | O_CREAT | O_APPEND, 0644);
	ft_putendl_fd(raw_line, fd_history);
	close(fd_history);
}

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

void	apply_custom_signal_handler(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &sig_handler);
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
	//is there a need to apply the original signal handler????????
	// here and int the exit_eof_or any other exit
	close(fd_stdin);
	close(fd_stdout);
	return (0);
}
