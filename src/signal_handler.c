/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:32:37 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/19 14:39:29 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sig_handler_running_command(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", STDIN_FILENO);
	}
	else if (sig == SIGQUIT)
	{
		printf("Quit: %d\n", sig);
	}
}

void	sig_handler_wait_for_command(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", STDIN_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_handler_heredoc(int sig)
{
	g_signal = sig;
	if (sig == SIGINT)
	{
		ioctl(0, TIOCSTI, "\n");
		printf(ANSI_MOVE_UP);
	}
}
