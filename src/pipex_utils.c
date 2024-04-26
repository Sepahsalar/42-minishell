/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:56:47 by asohrabi          #+#    #+#             */
/*   Updated: 2024/04/26 17:22:24 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// static char	*get_path_con(char **total_paths, char *cmd, char *temp)
// {
// 	char	*final_path;
// 
// 	while (*total_paths)
// 	{
// 		temp = ft_strjoin(*total_paths, "/");
// 		if (!temp)
// 		{
// 			ft_free(total_paths);
// 			error(EXIT_FAILURE);
// 		}
// 		final_path = ft_strjoin(temp, cmd);
// 		if (!final_path)
// 		{
// 			free(temp);
// 			ft_free(total_paths);
// 			error(EXIT_FAILURE);
// 		}
// 		free(temp);
// 		if (access(final_path, F_OK | X_OK) == 0)
// 			return (final_path);
// 		free(final_path);
// 		total_paths++;
// 	}
// 	return (0);
// }

// static char	*get_path(char *cmd, char **envp)
// {
// 	char	**total_paths;
// 	char	*final_path;

// 	while (*envp)
// 	{
// 		if (ft_strncmp(*envp, "PATH=", 5) == 0)
// 			break ;
// 		envp++;
// 	}
// 	if (!*envp)
// 	{
// 		ft_putstr_fd("Error: command not found: \n", STDERR_FILENO);
// 		exit(127);
// 	}
// 	total_paths = ft_split(*envp + 5, ':');
// 	if (!total_paths)
// 		error(EXIT_FAILURE);
// 	final_path = get_path_con(total_paths, cmd, NULL);
// 	if (!final_path)
// 	{
// 		ft_free(total_paths);
// 		return (NULL);
// 	}
// 	ft_free(total_paths);
// 	return (final_path);
// }

void	check_space(char *argv)
{
	char	*temp;

	temp = ft_strtrim(argv, " ");
	if (temp[0] == '\0')
	{
		ft_putstr_fd("Error: command not found: ", STDERR_FILENO);
		ft_putendl_fd(argv, STDERR_FILENO);
		exit(127);
	}
}

// static void	execute_cmd_helper(char **cmd, char *path, char **envp)
// {
// 	if (access(cmd[0], F_OK) == 0 && access(cmd[0], X_OK) == -1)
// 	{
// 		if (path != cmd[0])
// 			free(path);
// 		error(126);
// 	}
// 	if (execve(path, cmd, envp) == -1)
// 		error(EXIT_FAILURE);
// }

void	execute_cmd(t_cmd *cmd_start, t_cmd *cmd_execution)
{
// 	// char	**cmd;
// 	// char	*path;
// // 
// 	// check_space(argv);
// 	// cmd = ft_split(argv, ' ');
// 	// if (!cmd)
// 	// 	error(EXIT_FAILURE);
// 	// if (!ft_strchr(cmd[0], '/') && (cmd[0][0] != '.' && cmd[0][1] != '/'))
// 	// 	path = get_path(cmd[0], envp);
// 	// else
// 	// {
// 	// 	clean_cmd(cmd[0]);
// 	// 	path = cmd[0];
// 	// }
// 	// if (!path)
// 	// {
// 	// 	ft_free(cmd);
// 	// 	ft_putstr_fd("Error: command not found: ", STDERR_FILENO);
// 	// 	ft_putendl_fd(argv, STDERR_FILENO);
// 	// 	exit(127);
// 	// }
// 	// else
// 	// 	execute_cmd_helper(cmd, path, envp);
	char	*cmd_address = 0;
	char	**cmd_args = 0;
	char	**cmd_env = 0;
	t_file		*temp_file;
	t_file		*last_input = 0;
	t_file      *last_output = 0;
	int			fd[2];
	pid_t		pid;

	//Here_doc function
	temp_file = cmd_execution->input;
	while (temp_file)
	{
		if (temp_file->read == 0 && !temp_file->limiter)
		{
			if (temp_file->exist == 0)
			{
				printf("bash: %s: No such file or directory\n", temp_file->address);
				ft_master_clean(0 , cmd_start->env, cmd_start, 1);
			}
			else
			{
				printf("bash: %s: Permission denied\n", temp_file->address);
				ft_master_clean(0 , cmd_start->env, cmd_start, 1);
			}
		}
		temp_file = temp_file->next;
	}
	printf("end of input process\n");
	temp_file = cmd_execution->output;
	while (temp_file)
	{
		printf("we should not be here\n");
		if (temp_file->trunc)
			temp_file->fd = open(temp_file->address, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (temp_file->append)
		    temp_file->fd = open(temp_file->address, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (temp_file->fd == -1)
			ft_master_clean(0 , cmd_start->env, cmd_execution, 1);
		temp_file = temp_file->next;
	}
	printf("end of output process\n");
	if (cmd_execution->exec == 0)
	{
		if (cmd_execution->exist)
		{
		    printf("bash: %s: Permission denied\n", cmd_execution->cmd_name);
			ft_master_clean(0 , cmd_start->env, cmd_execution, 126);
		}
		else
		{
		    printf("bash: %s: command not found\n", cmd_execution->cmd_name);
			ft_master_clean(0 , cmd_start->env, cmd_execution, 127);
		}
	}
	printf("end of cmd check\n");
	last_input = ft_last_file(cmd_execution->input);
	if (last_input && !last_input->limiter)
	{
		last_input->fd = open(last_input->address, O_RDONLY);
		if (last_input->fd == -1)
		{
			printf("bash: %s: %s\n", last_input->raw, strerror(errno));
			ft_master_clean(0 , cmd_start->env, cmd_execution, 1);
		}
	}
	printf("end of opening input\n");
	//Handle here_doc
	temp_file = cmd_execution->output;
	//this part is the same as last file but for output
	while (temp_file)
	{
		printf("we should not be here\n");
		last_output = temp_file;
		if (temp_file->next)
			if (temp_file->fd > 2)
			{
			    close(temp_file->fd);
				temp_file->fd = -2;
				
			}
		temp_file = temp_file->next;
	}
	printf("end of last output\n");
	//printf("this is command number %d with last output address of %s with fd = %d\n", cmd_execution->index, last_output->address, last_output->fd);
	if (pipe(fd) == -1)
		ft_master_clean(0 , cmd_start->env, cmd_execution, 1);
	pid = fork();
	if (pid == -1)
		ft_master_clean(0 , cmd_start->env, cmd_execution, 1);
	if (pid == 0)
	{
		if (last_output)
		{
			if (dup2(last_output->fd, STDOUT_FILENO) == -1)
				ft_master_clean(0 , cmd_start->env, cmd_execution, 1);
		}
		else if (ft_cmd_count(cmd_start) > cmd_execution->index)
		{
			if (dup2(fd[1], STDOUT_FILENO) == -1)
				ft_master_clean(0 , cmd_start->env, cmd_execution, 1);
		}
		if (last_input && !last_input->limiter)
		{
			if (dup2(last_input->fd, STDIN_FILENO) == -1)
				ft_master_clean(0 , cmd_start->env, cmd_execution, 1);
		}
		else if (ft_cmd_count(cmd_start) > cmd_execution->index)
		{
			if (dup2(fd[0], STDIN_FILENO) == -1)
				ft_master_clean(0 , cmd_start->env, cmd_execution, 1);
		}
		// WE SHOULD HANDLE HEREDOC HERE
		close(fd[0]);
		close(fd[1]);
		ft_execution_package(cmd_execution, &cmd_address, &cmd_args, &cmd_env);
		// if (cmd_execution->error)
		// {
		// 	free(cmd_address);
		// 	ft_clean_2d_char(cmd_args);
		// 	ft_clean_2d_char(cmd_env);
		// 	ft_master_clean(0 , cmd_start->env, cmd_start, 1);
		// }
		//ft_master_clean(0 , cmd_start->env, cmd_start, -1);
		if (execve(cmd_address, cmd_args, 0) == -1)
		{
			perror("bash");
			free(cmd_address);
			ft_clean_2d_char(cmd_args);
			ft_clean_2d_char(cmd_env);
		}
	}
	else
	{
		//close(fd[1]);
		// if (last_output)
		// {
		// 	if (dup2(last_output->fd, STDIN_FILENO) == -1)
		// 		ft_master_clean(0 , cmd_start->env, cmd_execution, 1);
		// }
		// if (last_output)
		// {
		// 	if (dup2(STDIN_FILENO, last_output->fd) == -1)
		// 		ft_master_clean(0 , cmd_start->env, cmd_execution, 1);
		// }

		
		if (last_output)
		{
			close(0);
			dup(last_output->fd);
			close(last_output->fd);
		}
		else if (ft_cmd_count(cmd_start) > cmd_execution->index)
		{
			close(0);
			dup(fd[0]);
			// if (dup2(STDIN_FILENO, fd[0]) == -1)
			// 	ft_master_clean(0 , cmd_start->env, cmd_execution, 1);
		}
		

		
		// if (last_output && last_output->fd > 2)
		// {
		// 	close(last_output->fd);
		// 	last_output->fd = -2;
		// }
		// if (last_input && last_input->fd > 2)
		// {
		// 	close(last_input->fd);
		// 	last_input->fd = -2;
		// }
		
		close(fd[0]);
		close(fd[1]);
	}
}

