/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:06:56 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/19 16:40:35 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	running_command(void)
{
	struct termios	term;

	g_signal = 0;
	if (signal(SIGINT, &sig_handler_running_command) == SIG_ERR)
		return (1);
	if (signal(SIGQUIT, &sig_handler_running_command) == SIG_ERR)
		return (1);
	ft_bzero(&term, sizeof(term));
	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return (1);
	term.c_lflag |= ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		return (1);
	return (0);
}

static int	wait_for_command(void)
{
	struct termios	term;

	if (signal(SIGINT, &sig_handler_wait_for_command) == SIG_ERR)
		return (1);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (1);
	ft_bzero(&term, sizeof(term));
	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return (1);
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		return (1);
	return (0);
}

static int	heredoc_mode(void)
{
	struct termios	term;

	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (1);
	if (signal(SIGINT, &sig_handler_heredoc) == SIG_ERR)
		return (1);
	ft_bzero(&term, sizeof(term));
	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return (1);
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		return (1);
	return (0);
}

int	change_mode(int mode)
{
	if (mode == RUNNING_COMMAND)
	{
		if (running_command())
			return (1);
	}
	else if (mode == WAIT_FOR_COMMAND)
	{
		if (wait_for_command())
			return (1);
	}
	else if (mode == HEREDOC)
	{
		if (heredoc_mode())
			return (1);
	}
	return (0);
}
