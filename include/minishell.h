/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:36:16 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/24 10:20:49 by asohrabi         ###   ########.fr       */
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
# include <limits.h>

# define ANSI_COLOR_GREEN "\001\x1b[32m\002"
# define ANSI_COLOR_RESET "\001\x1b[0m\002"
# define ANSI_MOVE_UP "\033[1A"

# define WAIT_FOR_COMMAND 101
# define HEREDOC 102
# define HEREDOC_INTERRUPTED 103
# define RUNNING_COMMAND 0

extern volatile int	g_signal;

typedef struct s_file
{
	char			*raw;
	char			*address;
	int				exist;
	int				read;
	int				append;
	int				trunc;
	int				input;
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
	struct s_cmd	*previous;
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
	char	*fd;
	int		index;
	int		not_handling;
}			t_error;

typedef struct s_hd_file
{
	char	*str;
	t_file	*file;
}			t_hd_file;

typedef struct s_error_helper
{
	char	*token;
	int		index;
	int		sq;
	int		dq;
	t_error	error;
}			t_error_helper;

typedef struct s_open_quote
{
	int		sq;
	int		dq;
}			t_open_quote;

typedef struct s_dollar_helper
{
	t_dollar	*first;
	t_dollar	*new;
	t_dollar	*old;
	int			index;
	char		*sq;
	char		*dq;
	int			heredoc;
	int			type;
	int			id;
}				t_dollar_helper;

typedef struct s_file_helper
{
	int		index;
	int		sq;
	int		dq;
	int		len;
	t_file	*start;
	t_file	*new;
	t_file	*old;
}			t_file_helper;

void			rl_replace_line(const char *text, int clear_undo);
void			rl_clear_history(void);
void			clean_2d_char(char **array);
t_cmd			*clean_cmd_list(t_cmd *first);
t_cmd			*create_cmd_list(int total_number);
t_file			*clean_file_list(t_file *first);
char			**create_raw_cmd(const char *input);
int				char_2d_count(char **array);
int				fill_raw_cmd_list(t_cmd **cmd, char **raw_cmd);
void			fill_index_cmd_list(t_cmd **cmd);
char			*strdup_modified(char *s, char *token);
char			*ft_remove(char *str, char *del, t_file *file);
void			master_clean(char **raw_cmd, t_cmd *cmd,
					int exit_value);
t_cmd			*fill_cmd_list(char **raw_cmd, t_env *env, t_env *original_env);
void			clean_env_list(t_env *first);
t_env			*create_env_list(int total_number);
t_env			*fill_env_list(char **envp);
void			fill_env_cmd_list(t_cmd **cmd, t_env *env);
void			fill_original_env_cmd_list(t_cmd **cmd, t_env *original_env);
int				istoken(int c);
int				fill_files(t_cmd **cmd, char *token);
char			*dup_char(const char *s, char ch);
char			*dup_char_pipe(const char *s, char ch);
char			**create(const char *s, char ch, int i, int j);
char			**create_pipe(const char *s, char ch, int i, int j);
char			**split_pipex(const char *s);
char			**split_pipex_pipe(const char *s);
char			**split_all_delimiter(const char *s);
char			**free_split(char ***m, int j);
int				triger_maker(int triger, char ch, char divider);
int				len_helper(const char *s);
int				len_helper_pipe(const char *s);
int				fill_args_cmd_list(t_cmd **cmd);
int				check_accessibility(char *address, char mode);
char			*find_address(t_cmd *cmd, char mode);
int				find_cmd_address(t_cmd *cmd);
int				fill_address_access(t_cmd **cmd);
int				create_file_data(t_file *file);
int				fill_file_data(t_cmd **cmd);
char			*handling_quote(char *str);
t_env_pack		execute_cmd(t_cmd *cmd_start, t_cmd *cmd_execution);
int				ft_isspace(int ch);
char			**recreate_2d_env(t_env *env);
int				all_space(char *str);
char			**copy_2d_char(char **src);
void			execution_package(t_cmd *cmd,
					char **cmd_address, char ***cmd_args, char ***cmd_env);
int				cmd_count(t_cmd *cmd);
long			atoi_file(char **input, int place, int def);
int				fill_last_out(t_cmd **cmd);
t_last_file		*clean_last_file_list(t_last_file *first);
int				fill_last_in(t_cmd **cmd);
int				fd_heredoc(t_cmd **cmd_address);
int				fill_fd_heredoc(t_cmd **start_cmd);
int				check_unique(t_last_file *first, t_file *temp);
t_last_file		*create_last_file_node(t_file *file, t_file *temp);
t_last_file		*create_last_file_list(t_file *file);
int				handle_quote_cmd(t_cmd *start);
t_env_pack		execute_all(char *raw_line, t_env_pack env_pack);
void			fill_name_cmd_list(t_cmd **cmd);
t_dollar		*fill_dollar_list(char *arg);
char			*expand_dollar_helper(t_cmd *cmd, char *str,
					char *find, int type);
int				handle_dollar_struct(t_cmd *cmd);
char			*inside_double_quote(char *location);
char			*replace_inside(char *str, char *location,
					char *inside, char *handled_inside);
t_dollar		*clean_dollar_list(t_dollar *first);
void			remove_previous_node(t_dollar *current);
t_env_pack		run_env(t_cmd *cmd);
int				is_builtin(t_cmd *cmd);
t_env_pack		run_builtin(t_cmd *cmd);
t_env_pack		run_export(t_cmd *cmd);
t_env			*export_original(t_env *env, int status);
t_env_pack		init_env_pack(t_cmd *cmd);
int				same(char *s1, char *s2);
t_env			*remove_node(t_env *start, t_env *node);
t_env_pack		run_unset(t_cmd *cmd);
t_env_pack		run_pwd(t_cmd *cmd);
void			add_node_front(t_env **env, char *key, char *value);
t_env_pack		run_minishell(t_cmd *cmd);
t_env			*set_start(t_env *env);
t_env			*cpy_env(t_env *env);
char			*sliced_str(char *str, int start, int end);
t_env_pack		run_cd(t_cmd *cmd);
char			*value_finder(t_env *env, char *key);
t_env			*custom_export(t_env *env, char *key, char *value);
t_env_pack		run_echo(t_cmd *cmd);
t_env_pack		run_exit(t_cmd *cmd);
t_atol			atol_exit(char *str);
void			run_exit_eof(t_env *env);
t_error			find_error(char *line, t_env_pack env_pack);
char			*find_token(char *cur, t_env_pack env_pack);
char			*change_token(t_error_helper *e, char *cur,
					int *index, t_env_pack env_pack);
char			*change_token_heredoc(char *token, char *cur,
					int *index, t_env_pack env_pack);
int				check_after_token(char *str);
t_file			*create_file_node(int place);
int				fill_files_helper(char *str, char *ch, t_cmd *cmd);
int				fill_files_helper_all(t_cmd *cmd);
int				export_check(char *str);
int				export_check_key(char *str);
int				fill_files_all(t_cmd **cmd);
char			*get_current_pid(t_env *original_env);
void			sig_handler_running_command(int sig);
void			sig_handler_wait_for_command(int sig);
void			sig_handler_heredoc(int sig);
int				change_mode(int mode);
t_env_pack		not_handling_error(t_env_pack env_pack, t_error error);
int				print_error_before(t_error error, char *raw_line);
void			print_error_after(t_error error, int printed);
int				update_sq_dq_index(char c, int *sq, int *dq, int index);
int				open_sq_or_dq(char **token, int index);
t_env_pack		error_actions(t_env_pack env_pack,
					t_error error, char *raw_line);
t_env_pack		execute_actions(char *raw_line, t_env_pack env_pack);
int				accept_char(char *token, char *cur, t_env_pack env_pack);
t_env			*handle_oldpwd(t_env *env);
t_env			*sort_env(t_env *env);
int				env_count(t_env *env);
void			export_with_plus(t_cmd *cmd, char *arg, int *status);
void			print_export_error(char *arg, int *status);
void			export_no_arg(t_cmd *cmd);
t_quote			*create_and_fill_quote_list(char *str);
t_quote			*clean_quote_list(t_quote *first);
int				count_words(const char *s, char ch);
int				len_quote(const char *s, char ch);
int				len_quote_pipe(const char *s, char ch);
t_hd_file		*remove_update(t_hd_file *hd, char *ch);
t_hd_file		*remove_update_all(t_hd_file *hd);
t_env_pack		cmd_dir(t_cmd *cmd_execution, t_env_pack env_pack);
t_env_pack		empty_cmd_check(t_cmd *cmd_execution, t_env_pack env_pack);
t_env_pack		input_output_check_create(t_cmd *cmd_execution,
					t_env_pack env_pack);
void			input_output_open(t_cmd *cmd_start, t_cmd *cmd_execution);
void			input_output_open_helper(t_cmd *cmd_start, t_file *temp_file);
t_env_pack		full_cmd_check(t_cmd *cmd_execution, t_env_pack env_pack);
void			output_redirect_builtin(t_cmd *cmd_start,
					t_cmd *cmd_execution);
void			output_redirect(t_cmd *cmd_start,
					t_cmd *cmd_execution, int fd[2]);
void			output_redirect_builtin_helper(t_cmd *cmd_start,
					t_last_file *last);
void			output_redirect_helper(t_cmd *cmd_start,
					t_cmd *cmd_execution, int fd[2]);
void			input_redirect(t_cmd *cmd_start, t_cmd *cmd_execution);
t_env_pack		waiting_process(t_cmd *cmd_start, t_cmd *cmd_execution,
					t_env_pack env_pack);
t_env_pack		init_and_check(t_cmd *cmd_execution);
t_env_pack		parent_execution(t_cmd *cmd_start, t_cmd *cmd_execution,
					t_env_pack env_pack);
t_env_pack		after_child(t_cmd *cmd_start, t_cmd *cmd_execution,
					t_env_pack env_pack, int fd[2]);
void			input_output_redirect(t_cmd *cmd_start,
					t_cmd *cmd_execution, int fd[2]);
void			child_execution(t_cmd *cmd_start, t_cmd *cmd_execution,
					t_env_pack env_pack);
void			builtin_child_execution(t_cmd *cmd_execution,
					t_env_pack env_pack);
void			non_builtin_execution(t_cmd *cmd_start, t_cmd *cmd_execution);
void			child_process(t_cmd *cmd_start, t_cmd *cmd_execution,
					t_env_pack env_pack, int fd[2]);
int				should_execute_in_parent(t_cmd *cmd_start,
					t_cmd *cmd_execution);
int				type_finder(char *sq, char *dq, int heredoc);
t_dollar		*create_dollar_node(int id, char *place, int type);
void			run_execve(char *cmd_address, char **cmd_args, char **cmd_env);
void			handle_hd(t_cmd *cmd, t_handle_dollar *hd_pointer);
int				handle_dollar_string(t_cmd *cmd, char **string);
int				heredoc_actions(t_cmd *cmd, char **line, char **heredoc_text);
int				create_heredoc_file(t_cmd *cmd, t_file *temp_input);
t_error_helper	init_error_helper(void);
t_error			find_error_helper(char *line, char *token,
					int index, t_env_pack env_pack);
void			update_token_sq_dq(char **token, int *sq, int *dq, char c);
void			expand_two_dollars(t_cmd *cmd, char **str,
					char **find, int *remained_dollar);
int				no_need_more_expand(int remain_dollar, char *find, int type);
char			*str_after_expansion(char *str, char *find,
					char *variable, char *expanded);
char			*find_expanded(t_cmd *cmd, char *variable);
char			*find_var(char *find);
t_dollar_helper	init_dollar_helper(void);
void			sq_dq_heredoc_update(char *arg, t_dollar_helper *d);
int				should_create_node(char *arg, t_dollar_helper d);
t_file_helper	init_file_helper(char *str);
int				need_file_node_all(char *str, t_file_helper fh);
int				need_file_node_normal(char *str, char *ch, t_file_helper fh);
void			update_sq_dq_file(char *str, t_file_helper *fh);
int				need_update_sq_dq(char *str, t_file_helper fh);
int				save_history(char *raw_line, char *root);
int				load_history(char *root);
t_env_pack		fd_operator_check(t_cmd *cmd_execution,
					t_file *temp_file, t_env_pack env_pack);
t_env_pack		input_check(t_cmd *cmd_execution,
					t_file *temp_file, t_env_pack env_pack);
t_env_pack		output_check_create(t_cmd *cmd_execution,
					t_file *temp_file, t_env_pack env_pack);
t_env_pack		cmd_permission(t_cmd *cmd_execution, t_env_pack env_pack);
t_env_pack		cmd_not_found(t_cmd *cmd_execution, t_env_pack env_pack);
void			close_all(t_cmd *cmd);
void			clean_all(t_env *env1, t_env *env2, char *str1, char *str2);
int				clean_str(char *s1);
int				start_with_double_dot(char *arg);
char			*path_only_one_double_dot(t_env_pack env_pack);
char			*path_start_with_double_dot(t_cmd *cmd, t_env_pack env_pack);
t_env_pack		del_folder_one_dot(t_env_pack env_pack, t_cmd *cmd);
t_env_pack		del_folder_else(t_env_pack env_pack, t_cmd *cmd);
char			**init_token(t_env_pack env_pack);
t_error			init_error(void);
int				should_execute(char *raw_line);
t_env_pack		export_std_fd(t_env_pack env_pack);
void			history_management(t_env_pack env_pack, char *raw_line);
void			reset_std_fd(t_env_pack env_pack);
void			process_to_exit(t_env_pack env_pack);
void			minishell_process(t_env_pack env_pack);
void			dup_error(t_cmd *cmd);

#endif //MINISHELL_H