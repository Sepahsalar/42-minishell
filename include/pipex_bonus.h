/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:57:03 by asohrabi          #+#    #+#             */
/*   Updated: 2024/04/23 16:38:20 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../lib/libft/libft.h"
# include "minishell.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>

void	error(int status);
void	ft_free(char **array);
size_t	find_max(char *str1, char *str2);

void	here_doc(char *limiter);
void	clean_cmd(char *str);
int		open_file(char *argv, int i);

#endif
