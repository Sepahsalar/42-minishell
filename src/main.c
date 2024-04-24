/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:42:44 by nnourine          #+#    #+#             */
/*   Updated: 2024/04/24 16:15:24 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	**raw_cmd;
	t_env	*env;
	t_cmd	*cmd;
	//t_file	*f;


	(void)argc;
	raw_cmd = ft_create_raw_cmd(argv[1]);
	env = ft_fill_env_list(envp, raw_cmd);
	cmd = ft_fill_cmd_list(raw_cmd, env);
	// printf("chacking inputs\n");
	// f = cmd->input;
	// while (f)
	// {
	// 	printf("input: %s\n", f->address);
	// 	if (f->append == 1)
	// 	    printf("wtf: append\n");
	// 	if (f->trunc == 1)
	// 	    printf("wtf: trunc\n");
    //     f = f->next;
	// }
	// printf("chacking outputs\n");
	// f = cmd->output;
	// while (f)
	// {
	// 	printf("output: %s\n", f->address);
	// 	if (f->append == 1)
	// 	    printf("append\n");
	// 	if (f->trunc == 1)
	// 	    printf("trunc\n");
    //     f = f->next;
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
	ft_master_clean(raw_cmd, env, cmd, EXIT_SUCCESS);
}
