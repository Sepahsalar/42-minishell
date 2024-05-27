/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:42:44 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/27 19:03:06 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// 6) create a .history file to keep the commands for each SHLVL-------------8h denied
// 7) update SHLVL in env, so we can have multiple ./minishell 
//    inside of each other (like bash - like a builtin)----------------------4h half/done
// 8) error handling and leaks management after readline and before giving it
//    to execute command-----------------------------------------------------40h
// 8-1) (for this step, remind to handle this: '>|' '<>' '< |' '< <' '<<<')
// 8-2) handle "" as a command or a redirection
// 8-3) check "<<< end", it should do nothing but now it is creating heredoc that never ends
// 8-4) handle this:
// 		bash-3.2$ >>> hi
// 		bash: syntax error near unexpected token `>'
// 		bash-3.2$ > >> hi
// 		bash: syntax error near unexpected token `>>'
// 		bash-3.2$ << ls > >>
// 		bash: syntax error near unexpected token `>>'
// 9) handle ctrl + c & ctrl d inside of a heredoc---------------------------16h
//11) (bonus) handle "ls |" like a heredoc------------------------------------4h denied
//     قیل از هر چیز تریم اسپیس صورت گیرد.
// بعد از تریم اگر ایندکس منفی یک برابر پایپ بود هیر داک باز می شود و جوین صوزت می گیرد
// دوباره همین کار تکرار می شود

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

	status_last_cmd = 0;
	error = find_error(raw_line);
	if (error.error)
	{
		env_pack_result = env_pack;
		export_original(env_pack_result.original_env, 258);
		index = 0;
		token = NULL;
		heredoc_place = ft_strnstr(raw_line, "<<", error.index);
		if (!heredoc_place || check_after_token(raw_line + error.index
				+ ft_strlen(error.error) - 1))
		{
			printed = 1;
			printf("bash: syntax error near unexpected token `%s'\n",
				error.error);
		}
		while (index <= error.index)
		{
			token = change_token_heredoc(token, (raw_line + index),
					&index, error);
		}
		if (!printed)
			printf("bash: syntax error near unexpected token `%s'\n",
				error.error);
		return (env_pack_result);
	}
	raw_cmd = create_raw_cmd(raw_line);
	cmd = fill_cmd_list(raw_cmd, env_pack.env, env_pack.original_env);
	master_clean(raw_cmd, 0, 0, -1);
	cmd_counter = cmd_count(cmd);
	temp_cmd = cmd;
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
	t_env_pack 		env_pack;
	// struct sigaction	action;

	(void)argc;
	(void)argv;
	env_pack.env = set_start(fill_env_list(envp));
	env_pack.original_env = export_original(fill_env_list(envp), 0);
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
		if (!raw_line)
			run_exit_eof(env_pack.original_env, fd_stdin, fd_stdout);
		if (ft_strlen(raw_line) > 0 && !all_space(raw_line))
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
