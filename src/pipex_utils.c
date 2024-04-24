/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:56:47 by asohrabi          #+#    #+#             */
/*   Updated: 2024/04/24 16:26:04 by nnourine         ###   ########.fr       */
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
// 	char	*cmd_address;
// 	char	**cmd_args;
// 	char	**cmd_env;
	t_file		*temp_file;
	t_heredoc	*temp_heredoc;


	//////////////////////////////////////////////////////////////// CHECKING
	temp_heredoc = cmd_execution->limiter;
	while(temp_heredoc)
	{
		
	}
	temp_file = cmd_execution->input;
	while (temp_file)
	{
		if (temp_file->read == 0)
		{
			if (temp_file->exist == 0)
			{
				printf(" %s : No such file or directory\n", temp_file->address);
				//raw_cmd should be freed before this part, there is no use for it after cmd
				ft_master_clean(0 , cmd_start->env, cmd_start, 1);
			}
			else
			{
				// printf(" %s : Per\n", temp_file->address);
				perror("zsh");
				ft_master_clean(0 , cmd_start->env, cmd_start, 1);
			}
		}
		temp_file = temp_file->next;
	}
	temp_file = cmd_execution->input;
	while (temp_file)
	{
		if (temp_file->read == 0)
		{
			if (temp_file->exist == 0)
			{
				printf(" %s : No such file or directory\n", temp_file->address);
				//raw_cmd should be freed before this part, there is no use for it after cmd
				ft_master_clean(0 , cmd_start->env, cmd_start, 1);
			}
			else
			{
				// printf(" %s : Per\n", temp_file->address);
				perror("zsh");
				ft_master_clean(0 , cmd_start->env, cmd_start, 1);
			}
		}
		temp_file = temp_file->next;
	}
	temp_file = cmd_execution->output;
	while (temp_file)
	{
		if (temp_file->write == 0 && temp_file->exist == 1)
		{
			{
				// printf(" %s : Per\n", temp_file->address);
				perror("zsh");
				ft_master_clean(0 , cmd_start->env, cmd_start, 1);
			}
		}
		else if (temp_file->trunc == 1)
			temp_file->fd = open(temp_file->address, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (temp_file->append == 1)
			temp_file->fd = open(temp_file->address, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (temp_file->fd == -1)
			ft_master_clean(0 , cmd_start->env, cmd_start, 1);
		temp_file = temp_file->next;
	}


// 	////////////////////////////////////////////////////////////////

// 	ft_execution_package(cmd_execution, cmd_address, cmd_args, cmd_env);
// 	ft_master_clean(0 , cmd_start->env, cmd_start, -1);
// 	if (execve(cmd_address, cmd_args, cmd_env) == -1)
// 	{
// 		perror("zsh");
// 		free(cmd_address);
// 		ft_clean_2d_char(cmd_args);
// 		ft_clean_2d_char(cmd_env);
// 	}
}

