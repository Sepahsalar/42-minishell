/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:42:44 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/10 12:44:22 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


static int execute(char *raw_line, char **envp)
{
	char	**raw_cmd;
	t_env	*env;
	t_cmd	*cmd;
	t_cmd	*temp_cmd;
	int		status_last_cmd;
	int		cmd_count;
	t_file	*temp_file;
	
	status_last_cmd = 0;
	raw_cmd = ft_create_raw_cmd(raw_line);
	env = ft_fill_env_list(envp, raw_cmd);
	cmd = ft_fill_cmd_list(raw_cmd, env);
	ft_master_clean(raw_cmd, 0, 0, -1);
	cmd_count = ft_cmd_count(cmd);
	temp_cmd = cmd;
	while (temp_cmd)
	{
		if (temp_cmd->index == cmd_count)
			status_last_cmd = execute_cmd(cmd, temp_cmd);
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
	ft_master_clean(0, env, cmd, -1);
	return (status_last_cmd);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*raw_line;
// 	int		exit_code;


// 	(void)argc;
// 	(void)argv;
// 	while (1)
// 	{
// 		raw_line = readline("[minishell]$ ");
// 		if (ft_strlen(raw_line) > 0)
// 		{
// 			add_history(raw_line);
// 			exit_code = execute(raw_line, envp);
// 		}
// 		free(raw_line);
// 	}
// }

// void (*signal(int sig, void (*func)(int)))(int);

void	sigint_handler(int sig)
{
	//char    *raw_line;

	if (sig == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line(STDIN_FILENO, "");
		rl_on_new_line();
		// printf(ANSI_COLOR_GREEN "\n[ASAL]" ANSI_COLOR_RESET);
		// // printf("$");
		// rl_on_new_line();
		// raw_line = readline("$ ");
		// if (ft_strlen(raw_line) > 0)
		// 	return ;
		// else
		// {
		//     printf(ANSI_COLOR_GREEN "\n[ASAL]" ANSI_COLOR_RESET);
		// 	rl_redisplay();
		// 	// raw_line = readline("$ ");
		// }

		// free(raw_line);
        // printf("\n");
        // signal(SIGINT, SIG_DFL);
    }
		// printf("Asal is happy");
	
}


int	main(int argc, char **argv, char **envp)
{
	char	*raw_line;
	int		exit_code;

	(void)argc;
	(void)argv;
	signal(SIGINT, sigint_handler);
	while (1)
	{
		//signal(SIGINT, sigint_handler);
		printf(ANSI_COLOR_GREEN "[ASAL]" ANSI_COLOR_RESET);
		raw_line = readline("$ ");
		// if (raw_line == NULL)
		// {
		// 	// Handle EOF (Ctrl+D)
		// 	printf("\n");
		// 	// break ;
		// }
		// signal(SIGINT, SIG_DFL);
		if (ft_strlen(raw_line) > 0)
		{
			add_history(raw_line);
			exit_code = execute(raw_line, envp);
		}
		// signal(SIGINT, sigint_handler);
		free(raw_line);
	}
	return (exit_code);
}