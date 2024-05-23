# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 15:48:51 by nnourine          #+#    #+#              #
#    Updated: 2024/05/23 14:35:24 by asohrabi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Color
COLOR = \033[0;34m
RESET_COLOR = \033[0m

# Executable name
NAME = minishell

# Directories
SRCDIR = src
OBJDIR = obj
INCDIR = include
LIBFT = lib/libft

# Files
SRCS =  $(SRCDIR)/atoi_file.c \
		$(SRCDIR)/create_args.c \
		$(SRCDIR)/create_cmd_list.c \
		$(SRCDIR)/create_env_list.c \
		$(SRCDIR)/create_file_list.c \
		$(SRCDIR)/create_raw_cmd.c \
		$(SRCDIR)/execution_package.c \
		$(SRCDIR)/expand_dollar.c \
		$(SRCDIR)/fd_heredoc.c \
		$(SRCDIR)/fill_address_access.c \
		$(SRCDIR)/fill_cmd_list.c \
		$(SRCDIR)/fill_env_cmd_list.c \
		$(SRCDIR)/fill_env_list.c \
		$(SRCDIR)/fill_file_data.c \
		$(SRCDIR)/fill_files.c \
		$(SRCDIR)/fill_index_cmd_list.c \
		$(SRCDIR)/fill_last_file_utils.c \
		$(SRCDIR)/fill_last_file.c \
		$(SRCDIR)/fill_args_cmd_list.c \
		$(SRCDIR)/fill_raw_cmd_list.c \
		$(SRCDIR)/find_cmd_address.c \
		$(SRCDIR)/istoken.c \
		$(SRCDIR)/main.c \
		$(SRCDIR)/master_clean.c \
		$(SRCDIR)/pipex.c \
		$(SRCDIR)/recreate_2d_env.c \
		$(SRCDIR)/split_pipex.c \
		$(SRCDIR)/utility1.c \
		$(SRCDIR)/utility2.c \
		$(SRCDIR)/utility3.c \
		$(SRCDIR)/handle_quote.c \
		$(SRCDIR)/find_place_type_dollar.c \
		$(SRCDIR)/handle_dollar.c \
		$(SRCDIR)/builtin.c \
		$(SRCDIR)/env.c \
		$(SRCDIR)/export.c \
		$(SRCDIR)/unset.c \
		$(SRCDIR)/pwd.c \
		$(SRCDIR)/init_temp_env.c \
		$(SRCDIR)/cd.c \
		$(SRCDIR)/echo.c \
		$(SRCDIR)/exit.c \
		$(SRCDIR)/atol_exit.c \
		
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Compiler and flags
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
GENERAL_LIB_FLAGS = -L$(LIBFT) -lft
ADDRESS_SANITIZE = -fsanitize=address
LLDB = -g
READLINE = -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

# Phony targets
.PHONY: all clean fclean re address lldb

# Default target
all: $(NAME)

# Linking
$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT)
	@$(CC) $(CFLAGS) $(GENERAL_LIB_FLAGS) $(READLINE) $(OBJS) -o $@
	@echo "$(COLOR)Compiling and linking: done$(RESET_COLOR)"

# Compiling
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

# Clean-up
clean:
	@$(RM) -r $(OBJDIR)
	@$(MAKE) -C $(LIBFT) clean
	@echo "$(COLOR)Clean-up: done$(RESET_COLOR)"

# Full clean
fclean:
	@$(RM) -r $(OBJDIR)
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT) fclean
	@echo "$(COLOR)Full clean: done$(RESET_COLOR)"

# Recompile
re: fclean all

# Address sanitizer
address: fclean
address: CFLAGS += $(ADDRESS_SANITIZE)
address: all

# LLDB
lldb: fclean
lldb: CFLAGS += $(LLDB)
lldb: CC = clang
lldb: all