/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:32:37 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/07 11:21:38 by nnourine         ###   ########.fr       */
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
		printf("\033[1A");
		g_signal = HEREDOC_INTERRUPTED;
	}
}

t_signal	apply_custom_signal_handler(void)
{
	t_signal	old;
	t_signal	new;

	new.sig_quit.sa_handler = SIG_IGN;
	new.sig_quit.sa_flags = 0;
	sigemptyset(&new.sig_quit.sa_mask);
	new.sig_int.sa_handler = sig_handler;
	new.sig_int.sa_flags = 0;
	sigemptyset(&new.sig_int.sa_mask);
	sigaction(SIGINT, &new.sig_int, &old.sig_int);
	sigaction(SIGQUIT, &new.sig_quit, &old.sig_quit);
	return (old);
}
