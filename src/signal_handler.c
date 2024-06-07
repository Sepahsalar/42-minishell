/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:32:37 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/07 12:29:24 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT && g_signal == RUNNING_COMMAND)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", STDIN_FILENO);
	}
	else if (sig == SIGINT && g_signal == WAIT_FOR_COMMAND)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", STDIN_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGINT && g_signal == HEREDOC)
	{
		ioctl(0, TIOCSTI, "\n");
		printf(ANSI_MOVE_UP);
		g_signal = HEREDOC_INTERRUPTED;
	}
}

void	apply_custom_signal_handler(void)
{
	// t_signal	old;
	// t_signal	new;
//
	// new.sig_quit.sa_handler = SIG_IGN;
	// new.sig_quit.sa_flags = 0;
	// sigemptyset(&new.sig_quit.sa_mask);
	// new.sig_int.sa_handler = sig_handler;
	// new.sig_int.sa_flags = 0;
	// sigemptyset(&new.sig_int.sa_mask);
	// sigaction(SIGINT, &new.sig_int, &old.sig_int);
	// sigaction(SIGQUIT, &new.sig_quit, &old.sig_quit);
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
