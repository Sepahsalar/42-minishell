/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:42:44 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/30 18:02:37 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// 6) create a .history file to keep the commands for each SHLVL-------------8h denied
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
	int			index;
	char        *token;
	t_error		error;
	char		*heredoc_place;
	int			printed = 0;
	char		*sq;
	char    	*dq;

	sq = NULL;
	dq = NULL;
	status_last_cmd = 0;
	error = find_error(raw_line);
	env_pack_result = env_pack;
	if (error.error)
	{
		env_pack_result = env_pack;
		if (error.not_handling)
		{
			env_pack_result.original_env
				= export_original(env_pack_result.original_env, 1);
			ft_putstr_fd("ASAL: We are not going to handle `", 2);
			ft_putstr_fd(error.error, 2);
			ft_putendl_fd("\'", 2);
			return (env_pack_result);
		}
		export_original(env_pack_result.original_env, 258);
		index = 0;
		token = NULL;
		heredoc_place = ft_strnstr(raw_line, "<<", error.index);
		if (!heredoc_place || check_after_token(raw_line + error.index
				+ ft_strlen(error.error) - 1))
		{
			printed = 1;
			ft_putstr_fd("bash: syntax error near unexpected token `", 2);
			ft_putstr_fd(error.error, 2);
			ft_putendl_fd("\'", 2);
		}
		while (index <= error.index)
		{
			if (raw_line[index] == '\"' || raw_line[index] == '\'')
			{
				if (raw_line[index] == '\"' && dq == NULL)
					dq = &raw_line[index];
				else if (raw_line[index] == '\"')
					dq = NULL;
				else if (raw_line[index] == '\'' && sq == NULL)
					sq = &raw_line[index];
				else if (raw_line[index] == '\'')
					sq = NULL;
				index++;
			}
			else
			{
				if (sq || dq)
				{
					token = NULL;
					index++;
				}
				else
					token = change_token_heredoc(token, (raw_line + index),
							&index, error);
			}
		}
		if (!printed)
		{
			ft_putstr_fd("bash: syntax error near unexpected token `", 2);
			ft_putstr_fd(error.error, 2);
			ft_putendl_fd("\'", 2);
		}
		return (env_pack_result);
	}
	struct termios	term;

	ft_bzero(&term, sizeof(term));
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	g_signal = 0;
	raw_cmd = create_raw_cmd(raw_line);
	cmd = fill_cmd_list(raw_cmd, env_pack.env, env_pack.original_env);
	master_clean(raw_cmd, 0, 0, -1);
	cmd_counter = cmd_count(cmd);
	temp_cmd = cmd;
	if (!g_signal)
	{
		while (temp_cmd)
		{
			if (temp_cmd->index == cmd_counter)
			{
				env_pack_result = execute_cmd(cmd, temp_cmd);
			}
			else
				execute_cmd(cmd, temp_cmd);
			temp_cmd = temp_cmd->next;
		}
	}
	printf("i am after while loop\n");
	g_signal = 10;
	ft_bzero(&term, sizeof(term));
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	temp_cmd = cmd;
	while (temp_cmd)
	{
		ft_bzero(&term, sizeof(term));
		tcgetattr(STDIN_FILENO, &term);
		term.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
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

void	sig_handler(int sig)
{
	struct termios	term;
	// int				sign;

	// ft_bzero(&term, sizeof(term));
	// tcgetattr(STDIN_FILENO, &term);
	// // sign = g_signal;
	if (sig == SIGINT && g_signal == 0)
	{
		printf("i recieved the signal in the running mode\n");
		ft_bzero(&term, sizeof(term));
		tcgetattr(STDIN_FILENO, &term);
		term.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		// ioctl(0, TIOCSTI, "\n");
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		// printf(ANSI_MOVE_UP);
		rl_replace_line("", STDIN_FILENO);
		// printf("i am in 0\n");
		// g_signal = 10;
		
		// term.c_lflag |= ECHOCTL;
		// tcsetattr(STDIN_FILENO, TCSANOW, &term);
		// rl_on_new_line();
		// rl_redisplay();
		// rl_on_new_line();
		// ioctl(0, TIOCSTI, "\n");
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// // printf("\033[1A");
		// // printf(ANSI_MOVE_UP);
	}
	else if (sig == SIGINT && g_signal == 10)
	{
		// ft_bzero(&term, sizeof(term));
		// tcgetattr(STDIN_FILENO, &term);
		// term.c_lflag &= ~ECHOCTL;
		// tcsetattr(STDIN_FILENO, TCSANOW, &term);
		// ioctl(0, TIOCSTI, "\n");
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", STDIN_FILENO);
		// rl_on_new_line();
		rl_redisplay();
		
		// printf("i am in 10\n");
		// rl_on_new_line();
		// ioctl(0, TIOCSTI, "\n");
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// // printf("\033[1A");
		// // printf(ANSI_MOVE_UP);
	}
	// if (sign == 10)
	// 	term.c_lflag &= ~ECHOCTL;
	// else if (sign == 0)
	// 	term.c_lflag |= ECHOCTL;
	// tcsetattr(STDIN_FILENO, TCSANOW, &term);
	// else if (sig == SIGQUIT)
	// {
	// 	// rl_replace_line(0, STDIN_FILENO);
	// 	rl_on_new_line();
	// 	rl_redisplay();
	// }
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

int	main(int argc, char **argv, char **envp)
{
	char			*raw_line;
	int				exit_code;
	struct termios	term;
	int				fd_stdin;
	int				fd_stdout;
	t_env_pack 		env_pack;
	char 			*pid;
	t_env			*original_env;

	(void)argc;
	(void)argv;
	g_signal = 0;
	fd_stdin = dup(STDIN_FILENO);
	fd_stdout = dup(STDOUT_FILENO);
	env_pack.env = set_start(fill_env_list(envp));
	pid = get_current_pid(env_pack.env);
	dup(fd_stdin);
	close(STDOUT_FILENO);
	dup(fd_stdout);
	load_history();
	original_env = fill_env_list(envp);
	original_env = custom_export(original_env,
			ft_strdup("pid"), ft_strdup(pid));
	original_env = export_original(original_env, 0);
	env_pack.original_env = original_env;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &sig_handler);
	// ft_bzero(&term, sizeof(term));
	// tcgetattr(STDIN_FILENO, &term);
	// // // if (!g_signal)
	// 	term.c_lflag &= ~ECHOCTL;
	// // // else
	// // // 	term.c_lflag |= ECHOCTL;
	// tcsetattr(STDIN_FILENO, TCSANOW, &term);
	while (1)
	{
		// printf("i am here before getting raw_line\n");
		ft_bzero(&term, sizeof(term));
		tcgetattr(STDIN_FILENO, &term);
		term.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		raw_line = readline(ANSI_COLOR_GREEN "[ASAL]" ANSI_COLOR_RESET"$ ");
		if (!raw_line)
			run_exit_eof(env_pack.original_env, fd_stdin, fd_stdout);
		printf("i am here before checking raw_line: %s\n", raw_line);
		if (ft_strlen(raw_line) > 0 && !all_space(raw_line))
		{
			printf("i am here: %s\n", raw_line);
			g_signal = 0;
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
	close(fd_stdin);
	close(fd_stdout);
	return (exit_code);
}
