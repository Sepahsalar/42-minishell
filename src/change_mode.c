/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:06:56 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/05 10:45:42 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	running_command(void)
{
	struct termios	term;

	g_signal = RUNNING_COMMAND;
	ft_bzero(&term, sizeof(term));
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

static void	wait_for_command(void)
{
	struct termios	term;

	g_signal = WAIT_FOR_COMMAND;
	ft_bzero(&term, sizeof(term));
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

static void	heredoc_mode(void)
{
	struct termios	term;

	g_signal = HEREDOC;
	ft_bzero(&term, sizeof(term));
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	change_mode(int mode)
{
	if (mode == RUNNING_COMMAND)
		running_command();
	else if (mode == WAIT_FOR_COMMAND)
		wait_for_command();
	else if (mode == HEREDOC)
		heredoc_mode();
}
