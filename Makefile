# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/29 10:43:45 by asohrabi          #+#    #+#              #
#    Updated: 2024/06/19 11:20:38 by asohrabi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

HEADER	= -I ./include

FUNC =  src/atoi_utils.c \
		src/builtin.c \
		src/cd.c \
		src/change_mode.c \
		src/create_cmd_list.c \
		src/create_env_list.c \
		src/create_file_list.c \
		src/echo.c \
		src/env.c \
		src/exit.c \
		src/expand_dollar.c \
		src/expand_dollar_utils.c \
		src/expand_dollar_utils2.c \
		src/export.c \
		src/export_utils.c \
		src/export_utils2.c \
		src/export_check.c \
		src/fd_heredoc.c \
		src/fd_heredoc_utils.c \
		src/fill_cmd_list.c \
		src/fill_dollar_list.c \
		src/fill_dollar_list_utils.c \
		src/fill_dollar_list_utils2.c \
		src/fill_env_cmd_list.c \
		src/fill_env_list.c \
		src/fill_file_data.c \
		src/fill_files.c \
		src/fill_files_helper.c \
		src/fill_files_helper_utils.c \
		src/fill_files_helper_all.c \
		src/fill_index_cmd_list.c \
		src/fill_last_file.c \
		src/fill_last_file_utils.c \
		src/fill_raw_cmd_list.c \
		src/find_cmd_address.c \
		src/find_cmd_address_utils.c \
		src/ft_remove.c \
		src/handle_dollar.c \
		src/handle_history.c \
		src/handle_quote.c \
		src/handle_quote_utils.c \
		src/init_temp_env.c \
		src/istoken.c \
		src/main.c \
		src/master_clean.c \
		src/pipex.c \
		src/pipex_utils.c \
		src/pipex_child_dup_files.c \
		src/pipex_child_execution.c \
		src/pipex_parent_builtin_execution.c \
		src/pipex_check_files.c \
		src/pipex_cmd_errors.c \
		src/pipex_error_actions.c \
		src/pipex_error_actions_utils.c \
		src/pipex_error_handling.c \
		src/pipex_error_handling_utils.c \
		src/pipex_error_handling_utils2.c \
		src/pipex_error_handling_heredoc.c \
		src/pipex_execute_actions.c \
		src/pwd.c \
		src/recreate_2d_env.c \
		src/signal_handler.c \
		src/split_pipex.c \
		src/split_pipex_utils.c \
		src/split_pipex_utils2.c \
		src/unset.c \
		src/utility1.c \
		src/utility2.c \
		src/utility3.c \
		src/utility4.c \
		src/utility5.c \

OBJ = ${FUNC:.c=.o}

CFLAGS = -Wall -Wextra -Werror

%.o: %.c
	@cc ${CFLAGS} ${HEADER} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJ}
	@make -C ./lib/libft
	@cc ${CFLAGS} ${OBJ} -L./lib/libft -lft ${HEADER} -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include -o ${NAME}

clean:
	@rm -f ${OBJ} ${OBJ_BONUS}
	@make clean -C ./lib/libft

fclean: clean
	@rm -f ${NAME}
# @rm -f .history
	@make fclean -C ./lib/libft

re: fclean all

.PHONY: all, clean, fclean, re