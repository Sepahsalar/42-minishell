/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:42:44 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/20 19:58:52 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// 1) write env, unset and export builtin------------------------------------2h                                  
// 2) handle $? with export of a new variable n to the "original" env--------2h
// 3) take a look at the handle quote function-------------------------------8h
// 4) write other builtins and update the pipex functions--------------------16h
// 5) take a look at the readline function when cmd + c & cmd + v, also
// 	  when line is long------------------------------------------------------16h
// 6) create a .history file to keep the commands for each SHLVL-------------8h
// 7) update SHLVL in env, so we can have multiple ./minishell
//    inside of each other (like bash - like a builtin)----------------------4h
// 8) error handling after readline and before giving it to execute command--40h
// 9) handle ctrl + c & ctrl d inside of a heredoc---------------------------16h

t_env_pack	execute_all(char *raw_line, t_env_pack env_pack)
{
	char		**raw_cmd;
	t_cmd		*cmd;
	t_cmd		*temp_cmd;
	int			status_last_cmd;
	int			cmd_counter;
	t_file		*temp_file;
	t_env_pack	env_pack_result;

	status_last_cmd = 0;
	raw_cmd = create_raw_cmd(raw_line);
	cmd = fill_cmd_list(raw_cmd, env_pack.env, env_pack.original_env);
	master_clean(raw_cmd, 0, 0, -1);
	cmd_counter = cmd_count(cmd);
	temp_cmd = cmd;
	while (temp_cmd)
	{
		printf("start\n");
		if (temp_cmd->index == cmd_counter)
		{
			env_pack_result = execute_cmd(cmd, temp_cmd);
		}
		else
			execute_cmd(cmd, temp_cmd);
		printf("end\n");
		temp_cmd = temp_cmd->next;
	}
	printf("the exit code of this command is %s\n", env_pack_result.original_env->value);
	temp_cmd = cmd;
	while (temp_cmd)
	{
		if (temp_cmd->last_in)
			temp_file = temp_cmd->last_in->file;
		else
			temp_file = NULL;
		while (temp_file)
		{
			if (temp_file->limiter)
			{
				close(temp_file->fd); //maybe double close
				unlink(temp_file->address);
			}
			temp_file = temp_file->next;
		}
		temp_cmd = temp_cmd->next;
	}
	//master_clean(0, env, cmd, -1);
	return (env_pack_result);
}

static void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", STDIN_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

int	main(int argc, char **argv, char **envp)
{
	char			*raw_line;
	int				exit_code;
	struct termios	term;
	int				fd_stdin;
	int				fd_stdout;
	// t_env           *env;
	// t_env			*original_env;
	t_env_pack 		env_pack;
	// struct sigaction	action;

	(void)argc;
	(void)argv;
	env_pack.env = fill_env_list(envp);
	env_pack.original_env = fill_env_list(envp);
	env_pack.original_env = export_orginal(env_pack.original_env, 0);
	fd_stdin = dup(STDIN_FILENO);
	fd_stdout = dup(STDOUT_FILENO);
	signal(SIGQUIT, &sig_handler);
	signal(SIGINT, &sig_handler);
	// sigemptyset(&action.sa_mask);
	// action.sa_flags = SA_RESTART;
	// ft_memset(&action, 0, sizeof(action));
	// action.sa_handler = &sig_handler;
	// sigaction(SIGINT, &action, NULL);
	// sigaction(SIGQUIT, &action, NULL);
	ft_bzero(&term, sizeof(term));
	tcgetattr(STDIN_FILENO, &term);
	// if (mode)
	// 	terminal.c_lflag |= ECHOCTL;
	// else if (!mode)
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	while (1)
	{
		raw_line = readline(ANSI_COLOR_GREEN "[ASAL]" ANSI_COLOR_RESET"$ ");
		// raw_line = readline("[ASAL]$ ");
		if (!raw_line)
		{
			// here we should call our "exit" built-in function
			printf (ANSI_MOVE_UP ANSI_COLOR_GREEN "[ASAL]" ANSI_COLOR_RESET"$ exit\n");
			// printf (ANSI_MOVE_UP "[ASAL]$ exit\n");
			close(fd_stdin);
			close(fd_stdout);
			return (0);
		}
		if (ft_strlen(raw_line) > 0)
		{
			add_history(raw_line);
			env_pack = execute_all(raw_line, env_pack);
			close(STDIN_FILENO);
			dup(fd_stdin);
			close(STDOUT_FILENO);
			dup(fd_stdout);
		}
		free(raw_line);
	}
	close(fd_stdin);
	close(fd_stdout);
	return (exit_code);
}
