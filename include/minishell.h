/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:36:16 by nnourine          #+#    #+#             */
/*   Updated: 2024/04/23 15:07:20 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "../lib/libft/libft.h"
# include "pipex_bonus.h"


typedef struct s_file
{
	char			*raw;
	char			*address;
	int				exist;
	int				read;
	int				write;
	int				fd;
	struct s_file	*next;
}					t_file;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_heredoc
{
	char				*str;
	struct s_heredoc	*next;
}						t_heredoc;

typedef struct s_cmd
{
	int				index;
	char			*raw;
	char			*current;
	t_env			*env;
	t_heredoc		*limiter;
	t_file			*input;
	t_file			*output_trunc;
	t_file			*output_append;
	char			*cmd_name;
	char			*address;
	char			**args;
	int				exist;
	int				exec;
	int				error;
	struct s_cmd	*next;
}					t_cmd;

void		ft_clean_2d_char(char **array);
t_cmd		*ft_clean_cmd_list(t_cmd *first);
t_cmd		*ft_create_cmd_list(int total_number);
t_file		*ft_clean_file_list(t_file *first);
t_file		*ft_create_file_list(int total_number);
char		**ft_create_raw_cmd(const char *input);
int			ft_char_2d_count(char **array);
int			ft_fill_raw_cmd_list(t_cmd **cmd, char **raw_cmd);
void		ft_fill_index_cmd_list(t_cmd **cmd);
char		*ft_strdup_modified(char *s, char *token);
int			ft_fill_heredoc_cmd_list(t_cmd **cmd);
char		*ft_remove(char *str, char *del1, char *del2);
void		ft_master_clean(char **raw_cmd,
				t_env *env, t_cmd *cmd, int exit_value);
t_cmd		*ft_fill_cmd_list(char **raw_cmd, t_env *env);
char		**ft_copy_2d_char(char **array);
t_env		*ft_clean_env_list(t_env *first);
t_env		*ft_create_env_list(int total_number);
t_env		*ft_fill_env_list(char **envp, char **raw_cmd);
void		ft_fill_env_cmd_list(t_cmd **cmd, t_env *env);
t_heredoc	*ft_clean_heredoc_list(t_heredoc *first);
t_heredoc	*ft_create_heredoc_list(int total_number);
int			ft_token_count(char *str, char *token);
int			ft_istoken(int c);
int			ft_fill_files(t_cmd **cmd, char *token, int type);
int			master_pipex(int argc, char **argv, char **envp);
char		**ft_split_pipex(char const *s);
char		**ft_split_all_delimiter(char const *s);
char		**ft_free_split(char ***m, int j);
int			ft_triger_maker_sp(int triger, char c, char divider);
int			ft_len_helper(const char *s);
int			ft_handle_quote(char ***input);
char		**ft_create_args(char *str);
int			ft_fill_name_and_args_cmd_list(t_cmd **cmd);
void		ft_free_doule_and_single_pointer(char **m, char *s1, char *s2);
int			ft_accessibility(char *address, char mode);
int			ft_find_cmd_address(t_cmd *cmd);
int			ft_fill_address_access(t_cmd **cmd);
int			ft_create_file_data(t_file *file);
int			ft_fill_file_data(t_cmd **cmd);
char		*ft_handle_quote_str(char *input);

#endif //MINISHELL_H