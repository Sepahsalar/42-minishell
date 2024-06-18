/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:06:56 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/18 10:16:37 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	running_command(void)
{
	struct termios	term;

	g_signal = RUNNING_COMMAND;
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, &sig_handler);
	ft_bzero(&term, sizeof(term));
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (0);
}

static int	wait_for_command(void)
{
	struct termios	term;

	g_signal = WAIT_FOR_COMMAND;
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, SIG_IGN);
	ft_bzero(&term, sizeof(term));
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (0);
	
}

static int	heredoc_mode(void)
{
	struct termios	term;

	g_signal = HEREDOC;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &sig_handler);
	ft_bzero(&term, sizeof(term));
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL; ///why t does not know this
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
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
