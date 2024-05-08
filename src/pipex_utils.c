/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:56:47 by asohrabi          #+#    #+#             */
/*   Updated: 2024/05/08 17:17:13 by nnourine         ###   ########.fr       */
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

// void	check_space(char *argv)
// {
// 	char	*temp;

// 	temp = ft_strtrim(argv, " ");
// 	if (temp[0] == '\0')
// 	{
// 		ft_putstr_fd("Error: command not found: ", STDERR_FILENO);
// 		ft_putendl_fd(argv, STDERR_FILENO);
// 		exit(127);
// 	}
// }

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

int	execute_cmd(t_cmd *cmd_start, t_cmd *cmd_execution)
{
	char	*cmd_address;
	char	**cmd_args;
	char	**cmd_env;
	t_file	*temp_file;
	t_file	*last_input;
	t_file	*last_output;
	t_last_file	*last;
	int		fd[2];
	pid_t	pid;
	int     status;
	int		index;

	//check this: <<end 2<<not ./src/main.c cat
	status = 0;
	last_input = NULL;
	last_output = NULL;
	//ft_fd_heredoc(&cmd_execution);
	// //testing heredoc
	// if (cmd_execution->fd_heredoc != -2)
	// {
	// 	close(cmd_execution->fd_heredoc);
	// 	cmd_execution->fd_heredoc = open(cmd_execution->heredoc_file, O_RDONLY);
	// 	char *line;

	// 	line = get_next_line(cmd_execution->fd_heredoc);
	// 	printf("Start of heredoc file:\n");
	// 	while (line)
	// 	{
	// 		printf("1st printf: %s\n", line);
	// 		free(line);
	// 		line = get_next_line(cmd_execution->fd_heredoc);
	// 		printf("loop line: %s\n", line);
	// 	}
	// 	printf("End of heredoc file:\n");
	// }
	// printf("start of command %s in parent process\n", cmd_execution->raw);
	temp_file = cmd_execution->input;
	while (temp_file)
	{
		if (temp_file->read == 0 && !temp_file->limiter)
		{
			if (temp_file->exist == 0)
			{
				printf("bash: %s: No such file or directory\n",
					temp_file->address);
				ft_master_clean(0, cmd_start->env, cmd_start, -1);
				return (1);
			}
			else
			{
				printf("bash: %s: Permission denied\n", temp_file->address);
				ft_master_clean(0, cmd_start->env, cmd_start, -1);
				return (1);
			}
		}
		temp_file = temp_file->next;
	}
	temp_file = cmd_execution->output;
	while (temp_file)
	{
		if (temp_file->trunc)
			temp_file->fd = open(temp_file->address,
					O_RDWR | O_CREAT | O_TRUNC, 0644);
		else if (temp_file->append)
			temp_file->fd = open(temp_file->address,
					O_RDWR | O_CREAT | O_APPEND, 0644);
		if (temp_file->fd == -1)
		{
			ft_master_clean(0, cmd_start->env, cmd_execution, -1);
			return (1);
		}
		close(temp_file->fd);
		temp_file = temp_file->next;
	}
	if (cmd_execution->exec == 0)
	{
		if (cmd_execution->exist)
		{
			printf("bash: %s: Permission denied\n",
				cmd_execution->cmd_name);
			ft_master_clean(0, cmd_start->env, cmd_execution, -1);
			return (126);
		}
		else
		{
			printf("bash: %s: command not found\n",
				cmd_execution->cmd_name);
			ft_master_clean(0, cmd_start->env, cmd_execution, -1);
			return (127);
		}
	}


	
	// last_input = ft_last_file(cmd_execution->input);
	// if (last_input && !last_input->limiter)
	// {
	// 	last_input->fd = open(last_input->address, O_RDONLY);
	// 	if (last_input->fd == -1)
	// 	{
	// 		printf("bash: %s: %s\n", last_input->raw, strerror(errno));
	// 		ft_master_clean(0, cmd_start->env, cmd_execution, 1);
	// 	}
	// }



	
	//Handle here_doc
	// temp_file = cmd_execution->last_out;
	// //this part is the same as last file but for output
	// while (temp_file)
	// {
	// 	last_output = temp_file;
	// 	if (temp_file->next)
	// 	{
	// 		if (temp_file->fd > 2)
	// 		{
	// 			//close(temp_file->fd);
	// 			temp_file->fd = -2;
	// 		}
	// 	}
	// 	temp_file = temp_file->next;
	// }
	if (pipe(fd) == -1)
		ft_master_clean(0, cmd_start->env, cmd_execution, 1);
	pid = fork();
	if (pid == -1)
		ft_master_clean(0, cmd_start->env, cmd_execution, 1);
	if (pid == 0)
	{
		// printf("start of command %s in child process\n", cmd_execution->raw);
		// if (last_input && !last_input->limiter)
		// {
		// 	if (dup2(last_input->fd, STDIN_FILENO) == -1)
		// 		ft_master_clean(0, cmd_start->env, cmd_execution, 1);
		// 	// close(last_input->fd);
		// 	// last_input->fd = -2;
		// }
		// //Handle fd overflow before this point

		last = cmd_execution->last_in;
		if (last)
		{
			while (last)
			{
				last_input = last->file;
				// if (last_input->fd_operator <= 2 && !last_input->limiter)
				if (last_input->fd_operator <= 2)
				{
					last_input->fd = open(last_input->address, O_RDONLY);
					if (last_input->fd == -1)
						ft_master_clean(0, cmd_start->env, cmd_execution, 1);
					if (dup2(last_input->fd, last_input->fd_operator) == -1)
						ft_master_clean(0, cmd_start->env, cmd_execution, 1);
				}
				// else if (last_input->fd_operator <= 2 && last_input->limiter)
				// {
				// 	last_input->fd_heredoc = open(last_input->address, O_RDONLY);
				// 	if (last_input->fd_heredoc == -1)
				// 		ft_master_clean(0, cmd_start->env, cmd_execution, 1);
				// 	if (dup2(last_input->fd, last_input->fd_operator) == -1)
				// 		ft_master_clean(0, cmd_start->env, cmd_execution, 1);
				// }
				last = last->next;
			}
			// last_input = cmd_execution->input;
			// while (last_input)
			// {
			// 	if (last_input->fd_operator <= 2 && last_input->limiter)
			// 	{
			// 		here_doc(last_input);
			// 		//1)gathering info from stdin by creating temp files or using get next line and strjoin
			// 		//2)int index of heredoc = 1;
			// 		//3)char *name of file = temp + index of command + index of heredoc; in cleaning process they shuoud be deleted #for example temp_cmd1_1
			// 		//4)input->fd = open
			// 		//5)put_str_fd(fd, str)
			// 		//6) if (dup2(temp_file, last_input->fd_operator) == -1)
			// 		// 	ft_master_clean(0, cmd_start->env, cmd_execution, 1);
			// 		//7)index ++;
			// 	}
			// 	last = last->next;
			// }
			// last = cmd_execution->last_out;
			// while (last && last->file->fd_operator != 1)
			// 	last = last->next;
			// if (!last || last->file->fd_operator != 1)
			// {
			// 	dup2(fd[1], STDOUT_FILENO);
			// }
		}

		
		last = cmd_execution->last_out;
		
		if (last)
		{
			while (last)
			{
				last_output = last->file;
				if (last_output->fd_operator <= 2)
				{
					if (last_output->trunc)
						last_output->fd = open(last_output->address,
								O_RDWR | O_CREAT | O_TRUNC, 0644);
					else if (last_output->append)
						last_output->fd = open(last_output->address,
								O_RDWR | O_CREAT | O_APPEND, 0644);
					if (last_output->fd == -1)
						ft_master_clean(0, cmd_start->env, cmd_execution, 1);
					if (dup2(last_output->fd, last_output->fd_operator) == -1)
						ft_master_clean(0, cmd_start->env, cmd_execution, 1);
				}
				last = last->next;
			}
			last = cmd_execution->last_out;
			while (last && last->file->fd_operator != 1)
				last = last->next;
			if (!last || last->file->fd_operator != 1)
			{
				dup2(fd[1], STDOUT_FILENO);
			}
		}
		else if (ft_cmd_count(cmd_start) > cmd_execution->index)
		{
			if (dup2(fd[1], STDOUT_FILENO) == -1)
				ft_master_clean(0, cmd_start->env, cmd_execution, 1);
		}
		// WE SHOULD HANDLE HEREDOC HERE
		close(fd[0]);
		close(fd[1]);
		ft_execution_package(cmd_execution, &cmd_address, &cmd_args, &cmd_env);
		if (cmd_execution->error)
		{
			free(cmd_address);
			ft_clean_2d_char(cmd_args);
			ft_clean_2d_char(cmd_env);
			ft_master_clean(0, cmd_start->env, cmd_start, 1);
		}
		ft_master_clean(0, cmd_start->env, cmd_start, -1);
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
		close(fd[1]);
		// if (cmd_execution->fd != -2)
		// {
		// 	close(cmd_execution->fd);
		// 	// unlink(cmd_execution->heredoc_file);
		// }
		// if (cmd_execution->last_in)
		// 	temp_file = cmd_execution->last_in->file;
		// else
		// 	temp_file = NULL;
		// while (temp_file)
		// {
		// 	if (temp_file->limiter)
		// 	{
		// 		close(temp_file->fd); //maybe double close
		// 		unlink(temp_file->address);
		// 	}
		// 	temp_file = temp_file->next;
		// }
		if (cmd_execution->index < ft_cmd_count(cmd_start))
			dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		if (cmd_execution->index == ft_cmd_count(cmd_start))
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				status = WEXITSTATUS (status);
			else if (WIFSIGNALED(status))
				status = WTERMSIG(status) + 128;
			index = 1;
			while (index < cmd_execution->index)
			{
				wait(0);
				index++;
			}
			
			// temp_cmd = cmd_start;
			// printf("we are in the last command and we are setting the temp_cmd to %s\n", temp_cmd->raw);
			// while (temp_cmd)
			// {
			// 	if (temp_cmd->last_in)
			// 		temp_file = temp_cmd->last_in->file;
			// 	else
			// 		temp_file = NULL;
			// 	while (temp_file)
			// 	{
			// 		if (temp_file->limiter)
			// 		{
			// 			close(temp_file->fd); //maybe double close
			// 			unlink(temp_file->address);
			// 		}
			// 		temp_file = temp_file->next;
			// 	}
			// 	temp_cmd = temp_cmd->next;
			// }
		}
	}
	return (status);
}

