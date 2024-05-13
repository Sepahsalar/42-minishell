/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:42:44 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/13 18:19:17 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	execute(char *raw_line, char **envp)
{
	char	**raw_cmd;
	t_env	*env;
	t_cmd	*cmd;
	t_cmd	*temp_cmd;
	int		status_last_cmd;
	int		cmd_counter;
	t_file	*temp_file;

	status_last_cmd = 0;
	raw_cmd = create_raw_cmd(raw_line);
	env = fill_env_list(envp, raw_cmd);
	cmd = fill_cmd_list(raw_cmd, env);
	master_clean(raw_cmd, 0, 0, -1);
	cmd_counter = cmd_count(cmd);
	temp_cmd = cmd;
	while (temp_cmd)
	{
		if (temp_cmd->index == cmd_counter)
			status_last_cmd = execute_cmd(cmd, temp_cmd);
		else
			execute_cmd(cmd, temp_cmd);
		temp_cmd = temp_cmd->next;
	}
	// temp_cmd = cmd;
	// while(temp_cmd)
	// {
	// 	printf("raw_cmd:%s\n", temp_cmd->raw);
	// 	printf("current_cmd:%s\n", temp_cmd->current);
	// 	printf("cmd_ADD:%s\n", temp_cmd->address);
	// 	printf("cmd_NAME:%s\n", temp_cmd->cmd_name);
	// 	printf("cmd_arg0:%s\n", temp_cmd->args[0]);
	// 	printf("cmd_arg1:%s\n", temp_cmd->args[1]);
	// 	printf("cmd_exist:%d\n", temp_cmd->exist);
	// 	printf("cmd_execute:%d\n", temp_cmd->exec);
	// 	temp_cmd = temp_cmd->next;
	// }
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
	// c = cmd;
	// i = 1;
	// while (c)
	// {
	// 	printf("we are in cmd number %d\n", i);
	// 	printf("*****checking inputs\n");
	// 	f = c->input;
	// 	while (f)
	// 	{
	// 		printf("input raw: %s\n", f->raw);
	// 		printf("input address: %s\n", f->address);
	// 		printf("input read: %d\n", f->read);
	// 		printf("input write: %d\n", f->write);
	// 		printf("input exist: %d\n", f->exist);
	// 		if (f->append == 1)
	// 			printf("wtf: append\n");
	// 		if (f->trunc == 1)
	// 			printf("wtf: trunc\n");
	// 		if (f->limiter)
	// 			printf("limiter is %s\n", f->limiter);
	// 		f = f->next;
	// 	}
	// 	printf("*****checking outputs\n");
	// 	f = c->output;
	// 	while (f)
	// 	{
	// 		printf("output raw: %s\n", f->raw);
	// 		printf("output address: %s\n", f->address);
	// 		printf("output read: %d\n", f->read);
	// 		printf("output write: %d\n", f->write);
	// 		printf("output exist: %d\n", f->exist);
	// 		if (f->append == 1)
	// 			printf("append\n");
	// 		if (f->trunc == 1)
	// 			printf("trunc\n");
	// 		if (f->limiter)
	// 			printf("limiter is %s\n", f->limiter);
	// 		f = f->next;
	// 	}
	// 	c = c->next;
	// 	i++;
	// 	printf("\n\n");
	// }
	//master_pipex(cmd);
	// temp = cmd;
	// while (temp)
	// {
	// 	printf("command:%s\n", temp->cmd_name);
	// 	if (temp->output_trunc)
	// 		printf("outfile:%s\n", (temp->output_trunc)->address);
	// 	temp = temp->next;
	// }
	master_clean(0, env, cmd, -1);
	return (status_last_cmd);
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
	char				*raw_line;
	int					exit_code;
	// struct sigaction	action;
	struct termios		term;

	(void)argc;
	(void)argv;
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
		{
			// here we should call our "exit" built-in function
			printf (ANSI_MOVE_UP ANSI_COLOR_GREEN "[ASAL]" ANSI_COLOR_RESET"$ exit\n");
			return (0);
		}
		if (ft_strlen(raw_line) > 0)
		{
			add_history(raw_line);
			exit_code = execute(raw_line, envp);
		}
		free(raw_line);
	}
	return (exit_code);
}
