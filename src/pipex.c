/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:56:21 by asohrabi          #+#    #+#             */
/*   Updated: 2024/04/23 17:22:21 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	child_process(t_cmd *cmd)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		error(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		error(EXIT_FAILURE);
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			error(EXIT_FAILURE);
		close(fd[1]);
		execute_cmd(cmd);
	}
	else
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			error(EXIT_FAILURE);
		close(fd[0]);
	}
}

static int	status_check(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS (status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	else
		return (1);
}

// static int	pipex_helper(int argc, char **argv)
// {
// 	int	filein;
// 	int	fileout;
// 	int	i;

// 	if (ft_strncmp(argv[1], "here_doc", find_max(argv[1], "here_doc")) == 0)
// 	{
// 		i = 3;
// 		fileout = open_file(argv[argc - 1], 2);
// 		here_doc(argv[2]);
// 	}
// 	else
// 	{
// 		i = 2;
// 		fileout = open_file(argv[argc - 1], 1);
// 		filein = open_file(argv[1], 0);
// 
// 		if (dup2(filein, STDIN_FILENO) == -1)
// 			error(EXIT_FAILURE);
// 		close(filein);
// 	}
// 	if (dup2(fileout, STDOUT_FILENO) == -1)
// 		error(EXIT_FAILURE);
// 	close(fileout);
// 	return (i);
// }

// static int	pipex(int argc, char **argv, char **envp)
// {
// 	int		i;
// 	int		j;
// 	int		status;
// 	pid_t	pid;

// 	status = 0;
// 	i = pipex_helper(argc, argv);
// 	j = i;
// 	while (i < argc - 2)
// 		child_process(argv[i++], envp);
// 	pid = fork();
// 	if (pid == -1)
// 		error(EXIT_FAILURE);
// 	if (pid == 0)
// 		execute_cmd(argv[argc - 2], envp);
// 	else
// 	{
// 		waitpid(pid, &status, 0);
// 		while (j < argc - 2)
// 		{
// 			wait(0);
// 			j++;
// 		}
// 	}
// 	return (status_check(status));
// }

static int	pipex(t_cmd *cmd)
{
	int		status;
	pid_t	pid;
	int		cmd_counter;
	t_cmd	*temp_cmd;
	int		index;

	temp_cmd = cmd;
	cmd_counter = 0;
	while (temp_cmd)
	{
		temp_cmd = temp_cmd->next;
		cmd_counter++;
	}
	status = 0;
	index = 1;
	temp_cmd = cmd;
	while (index < cmd_counter)
	{
		child_process(temp_cmd);
		temp_cmd = temp_cmd->next;
		index++;
	}
	pid = fork();
	if (pid == -1)
		error(EXIT_FAILURE);
	if (pid == 0)
		execute_cmd(temp_cmd);
	else
	{
		waitpid(pid, &status, 0);
		index = 1;
		while (index < cmd_counter)
		{
			wait(0);
			index++;
		}
	}
	return (status_check(status));
}

// int	master_pipex(int argc, char **argv, char **envp)
// {
// 	int	status;

// 	status = 0;
// 	if (argc < 5
// 		|| (ft_strncmp(argv[1], "here_doc", find_max(argv[1], "here_doc")) == 0
// 			&& argc != 6))
// 	{
// 		ft_putendl_fd("Error: Wrong Arguments!", STDERR_FILENO);
// 		ft_putendl_fd("Ex: ./pipex infile cmd1 cmd2 ... outfile",
// 			STDERR_FILENO);
// 		ft_putendl_fd("Ex: ./pipex \"here_doc\" LIMITER cmd cmd1 outfile",
// 			STDERR_FILENO);
// 		exit(EXIT_FAILURE);
// 	}
// 	else
// 	{
// 		status = pipex(argc, argv, envp);
// 	}
// 
// 	return (status);
// }

int	master_pipex(t_cmd *cmd)
{
	int	status;

	status = 0;
	// if (argc < 5
	// 	|| (ft_strncmp(argv[1], "here_doc", find_max(argv[1], "here_doc")) == 0
	// 		&& argc != 6))
	// {
	// 	ft_putendl_fd("Error: Wrong Arguments!", STDERR_FILENO);
	// 	ft_putendl_fd("Ex: ./pipex infile cmd1 cmd2 ... outfile",
	// 		STDERR_FILENO);
	// 	ft_putendl_fd("Ex: ./pipex \"here_doc\" LIMITER cmd cmd1 outfile",
	// 		STDERR_FILENO);
	// 	exit(EXIT_FAILURE);
	// }
	// else
	// {
	status = pipex(cmd);
	// }
		
	return (status);
}
