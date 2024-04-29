/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:42:44 by nnourine          #+#    #+#             */
/*   Updated: 2024/04/29 11:16:27 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	**raw_cmd;
	t_env	*env;
	t_cmd	*cmd;
	// t_file	*f;
	t_cmd	*temp_cmd;
	int		status;


	(void)argc;
	status = 0;
	raw_cmd = ft_create_raw_cmd(argv[1]);
	env = ft_fill_env_list(envp, raw_cmd);
	cmd = ft_fill_cmd_list(raw_cmd, env);
	ft_master_clean(raw_cmd, 0, 0, -1);
	temp_cmd = cmd;
	while (temp_cmd)
	{
		status = execute_cmd(cmd, temp_cmd);
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
	ft_master_clean(0, env, cmd, status);
}
