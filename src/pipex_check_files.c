/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_check_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:44:25 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/18 18:39:15 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env_pack	init_and_check(t_cmd *cmd_start, t_cmd *cmd_execution)
{
	t_env_pack	env_pack;

	env_pack = init_env_pack(cmd_execution);
	env_pack = input_output_check_create(cmd_start, cmd_execution, env_pack);
	env_pack = empty_cmd_check(cmd_start, cmd_execution, env_pack);
	env_pack = full_cmd_check(cmd_start, cmd_execution, env_pack);
	return (env_pack);
}

t_env_pack	input_output_check_create(t_cmd *cmd_start, t_cmd *cmd_execution,
	t_env_pack env_pack)
{
	t_file		*temp_file;

	temp_file = cmd_execution->all;
	while (temp_file)
	{
		env_pack = fd_operator_check(cmd_start, cmd_execution,
				temp_file, env_pack);
		if (cmd_execution->file_error)
			break ;
		if (temp_file->input)
			env_pack = input_check(cmd_start, cmd_execution,
					temp_file, env_pack);
		else if (temp_file->trunc || temp_file->append)
			env_pack = output_check_create(cmd_start, cmd_execution,
					temp_file, env_pack);
		if (temp_file->fd == -1)
			break ;
		if (temp_file->fd > 2)
			close(temp_file->fd);
		temp_file = temp_file->next;
	}
	return (env_pack);
}

t_env_pack	fd_operator_check(t_cmd *cmd_start, t_cmd *cmd_execution,
	t_file *temp_file, t_env_pack env_pack)
{
	char	*fd_operator;

	if (temp_file->fd_operator > RE_DUP_MAX) //find sth for it
	{
		env_pack.original_env
			= export_original(env_pack.original_env, 1);
		cmd_execution->file_error = 1;
		ft_putstr_fd("bash: ", 2);
		if (temp_file->fd_operator <= INT_MAX)
		{
			fd_operator = ft_itoa(temp_file->fd_operator);
			if (!fd_operator)
				master_clean(NULL, cmd_start, EXIT_FAILURE);
			ft_putstr_fd(fd_operator, 2);
			free(fd_operator);
		}
		else
			ft_putstr_fd("file descriptor out of range", 2);
		ft_putendl_fd(": Bad file descriptor", 2);
	}
	return (env_pack);
}

t_env_pack	input_check(t_cmd *cmd_start, t_cmd *cmd_execution,
	t_file *temp_file, t_env_pack env_pack)
{
	if (!temp_file->limiter)
	{
		temp_file->fd = open(temp_file->address, O_RDONLY);
		if (temp_file->fd == -1)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(temp_file->address, 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd(strerror(errno), 2);
			env_pack.original_env
				= export_original(env_pack.original_env, 1);
			cmd_execution->file_error = 1;
			(void)cmd_start;
		}
	}
	return (env_pack);
}

t_env_pack	output_check_create(t_cmd *cmd_start, t_cmd *cmd_execution,
	t_file *temp_file, t_env_pack env_pack)
{
	if (temp_file->trunc)
		temp_file->fd = open(temp_file->address,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (temp_file->append)
		temp_file->fd = open(temp_file->address,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (temp_file->fd == -1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(temp_file->address, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		(void)cmd_start;
		env_pack.original_env
			= export_original(env_pack.original_env, 1);
		cmd_execution->file_error = 1;
	}
	return (env_pack);
}
