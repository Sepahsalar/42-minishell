/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:36:16 by nnourine          #+#    #+#             */
/*   Updated: 2024/04/19 09:34:18 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "../lib/libft/libft.h"

typedef struct s_file
{
	char			*raw;
	char			*address;
	int				exist;
	int				read;
	int				write;
	int				fd;
	int				trunc;
	int				append;
	struct s_file	*next;
}					t_file;

typedef struct s_cmd
{
	int				index; //might need to be deleted
	char			*raw;
	char			*current;
	char			*cmd_error;
	char			*cmd_name;
	char			*address;
	char			**args;
	char			**envs;
	int				exist;
	int				exec;
	char			*limiter;
	t_file			*input;
	t_file			*output;
	struct s_cmd	*next;
}					t_cmd;

void	ft_clean_2d_char(char **array);
t_cmd	*ft_clean_cmd_list(t_cmd *first);
t_cmd	*ft_create_cmd_list(int total_number);
t_file	*ft_clean_file_list(t_file *first);
t_file	*ft_create_file_list(int total_number);
char	**ft_create_raw_cmd(const char *input);
int		ft_cmd_count(char **raw_cmd);
int		ft_fill_raw_cmd_list(t_cmd **cmd, char **raw_cmd);
void	ft_fill_index_cmd_list(t_cmd **cmd);
char	*ft_strdup_modified(char *s, char *token);
int		ft_fill_heredoc_cmd_list(t_cmd **cmd);
char	*ft_remove(char *str, char *del1, char *del2);
int		ft_master_clean(char **raw_cmd, t_cmd *cmd, int return_value);

#endif //MINISHELL_H
