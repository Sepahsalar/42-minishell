/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:36:16 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/03 14:24:33 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <string.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/ioctl.h>

# define ANSI_COLOR_GREEN "\001\x1b[32m\002"
# define ANSI_COLOR_RESET "\001\x1b[0m\002"
// # define ANSI_MOVE_UP "\033[1A"

// # define ANSI_SAVE_CURSOR "\033[s"
// # define ANSI_RESTORE_CURSOR "\033[u"
// # define ANSI_MOVE_TO_END "\033[K"
// # define ANSI_MOVE_LEFT "\033[8D"
// # define ANSI_MOVE_RIGHT "\033[C"


# define WAIT_FOR_COMMAND 10
# define HEREDOC 20
# define HEREDOC_INTERRUPTED 30
# define RUNNING_COMMAND 0

volatile int g_signal;

typedef struct s_file
{
	char			*raw;
	char			*address;
	int				exist;
	int				read;
	int				append;
	int				trunc;
	int				input;
	int				ignore;
	char			*limiter;
	int				write;
	int				fd;
	long			fd_operator;
	int				place;
	struct s_file	*next;
}					t_file;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				index;
	struct s_env	*next;
}					t_env;

typedef struct s_last_file
{
	t_file				*file;
	struct s_last_file	*next;
}						t_last_file;

typedef struct s_cmd
{
	int				index;
	char			*raw;
	char			*current;
	t_env			*env;
	t_env			*original_env;
	t_file			*input;
	t_file			*output;
	t_last_file		*last_in;
	t_last_file		*last_out;
	t_file			*std_error;
	t_file			*all;
	int				is_file;
	int				file_error;
	int				child_builtin;
	int				empty_cmd;
	char			*cmd_name;
	char			*address;
	char			**args;
	int				exist;
	int				exec;
	int				dir;
	int				error;
	pid_t			pid;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_dollar
{
	int				id;
	char			*place;
	int				type;
	struct s_dollar	*previous;
	struct s_dollar	*next;
}					t_dollar;

typedef struct s_handle_dollar
{
	char		*str;
	t_dollar	*dollar;
}				t_handle_dollar;

typedef struct s_env_pack
{
	t_env	*env;
	t_env	*original_env;
}			t_env_pack;

typedef struct s_quote
{
	int				start;
	int				end;
	struct s_quote	*next;
}					t_quote;

typedef struct s_atoi_file
{
	char	*str;
	int		place;
	long	res;
	int		flag;
}			t_atoi_file;

typedef struct s_atol
{
	long	num;
	int		is_error;
	int		sign;
	int		i;
}			t_atol;

typedef struct s_error
{
	char	*error;
	int		index;
	int		not_handling;
}			t_error;

typedef struct s_hd_file
{
	char	*str;
	t_file	*file;
}			t_hd_file;

void		rl_replace_line(const char *text, int clear_undo);
void		rl_clear_history(void);
void		clean_2d_char(char **array);
t_cmd		*clean_cmd_list(t_cmd *first);
t_cmd		*create_cmd_list(int total_number);
t_file		*clean_file_list(t_file *first);
char		**create_raw_cmd(const char *input);
int			char_2d_count(char **array);
int			fill_raw_cmd_list(t_cmd **cmd, char **raw_cmd);
void		fill_index_cmd_list(t_cmd **cmd);
char		*strdup_modified(char *s, char *token);
char		*ft_remove(char *str, char *del, t_file *file);
void		master_clean(char **raw_cmd,
				t_env *env, t_cmd *cmd, int exit_value);
t_cmd		*fill_cmd_list(char **raw_cmd, t_env *env, t_env *original_env);
t_env		*clean_env_list(t_env *first);
t_env		*create_env_list(int total_number);
t_env		*fill_env_list(char **envp);
void		fill_env_cmd_list(t_cmd **cmd, t_env *env);
void		fill_original_env_cmd_list(t_cmd **cmd, t_env *original_env);
int			istoken(int c);
int			fill_files(t_cmd **cmd, char *token);
char		**split_pipex(char const *s);
char		**split_pipex_pipe(char const *s);
char		**split_all_delimiter(char const *s);
char		**free_split(char ***m, int j);
int			triger_maker_sp(int triger, char ch, char divider);
int			len_helper(const char *s);
int			len_helper_pipe(const char *s);
int			fill_args_cmd_list(t_cmd **cmd);
int			check_accessibility(char *address, char mode);
int			find_cmd_address(t_cmd *cmd);
int			fill_address_access(t_cmd **cmd);
int			create_file_data(t_file *file);
int			fill_file_data(t_cmd **cmd);
char		*handling_quote(char *str);
t_env_pack	execute_cmd(t_cmd *cmd_start, t_cmd *cmd_execution);
int			ft_isspace(int ch);
char		**recreate_2d_env(t_env *env);
int			all_space(char *str);
char		**copy_2d_char(char **src);
void		execution_package(t_cmd *cmd,
				char **cmd_address, char ***cmd_args, char ***cmd_env);
int			cmd_count(t_cmd *cmd);
long		atoi_file(char **input, int place, int def);
int			fill_last_out(t_cmd **cmd);
t_last_file	*clean_last_file_list(t_last_file *first);
int			fill_last_in(t_cmd **cmd);
int			fd_heredoc(t_cmd **cmd_address);
int			fill_fd_heredoc(t_cmd **start_cmd);
int			check_unique(t_last_file *first, t_file *temp);
t_last_file	*create_last_file_node(t_file *file, t_file *temp);
t_last_file	*create_last_file_list(t_file *file);
int			handle_quote_cmd(t_cmd *start);
t_env_pack	execute_all(char *raw_line, t_env_pack env_pack);
void		fill_name_cmd_list(t_cmd **cmd);
t_dollar	*create_fill_dollar_list(char *arg);
char		*expand_dollar_helper(t_cmd *cmd, char *str, char *find, int type);
int			handle_dollar_struct(t_cmd *cmd);
char		*inside_double_quote(char *location);
char		*replace_inside(char *str, char *location,
				char *inside, char *handled_inside);
t_dollar	*clean_dollar_list(t_dollar *first);
void		remove_previous_node(t_dollar *current);
t_env_pack	run_env(t_cmd *cmd);
int			is_builtin(t_cmd *cmd);
t_env_pack	run_builtin(t_cmd *cmd);
t_env_pack	run_export(t_cmd *cmd);
t_env		*export_original(t_env *env, int status);
t_env_pack	init_env_pack(t_cmd *cmd);
int			same(char *s1, char *s2);
t_env		*remove_node(t_env *start, t_env *node);
t_env_pack	run_unset(t_cmd *cmd);
t_env_pack	run_pwd(t_cmd *cmd);
void		add_node_front(t_env **env, char *key, char *value);
t_env_pack	run_minishell(t_cmd *cmd);
t_env		*set_start(t_env *env);
t_env		*cpy_env(t_env *env);
char		*sliced_str(char *str, int start, int end);
t_env_pack	run_cd(t_cmd *cmd);
char		*value_finder(t_env *env, char *key);
t_env		*custom_export(t_env *env, char *key, char *value);
t_env_pack	run_echo(t_cmd *cmd);
t_env_pack	run_exit(t_cmd *cmd);
t_atol		atol_exit(char *str);
void		run_exit_eof(t_env *env, int fd_stdin, int fd_stdout);
t_error		find_error(char *line);
char		*find_token(char *cur);
char		*change_token(char *token, char *cur, int *index, int sq_dq);
char		*change_token_heredoc(char *token, char *cur,
				int *index, t_error error);
int			check_after_token(char *str);
t_file		*create_file_node(int place);
int			fill_files_helper(char *str, char *ch, t_cmd *cmd);
int			fill_files_helper_all(t_cmd *cmd);
int			export_check(char *str);
int			export_check_key(char *str);
int			fill_files_all(t_cmd **cmd);
char		*get_current_pid(t_env *original_env);
void		sig_handler(int sig);
void		change_mode(int mode);
t_env_pack	not_handling_error(t_env_pack env_pack, t_error error);
int			print_error_before(t_error error, char *raw_line);
void		print_error_after(t_error error, int printed);
int			update_sq_dq_index(char c, int *sq, int *dq, int index);
int			open_sq_or_dq(char **token, int index);
t_env_pack	error_actions(t_env_pack env_pack, t_error error, char *raw_line);
t_env_pack	execute_actions(char *raw_line, t_env_pack env_pack);
int			accept_char(char *token, char *cur);

#endif //MINISHELL_H