/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:32:37 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/05 11:33:21 by asohrabi         ###   ########.fr       */
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

void	apply_custom_signal_handler(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &sig_handler);
}
