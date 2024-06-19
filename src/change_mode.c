/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:06:56 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/19 14:40:10 by nnourine         ###   ########.fr       */
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

	// g_signal = WAIT_FOR_COMMAND;
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

	// g_signal = HEREDOC;
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
