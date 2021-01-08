# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aboutahr <aboutahr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/19 13:04:45 by aamzil            #+#    #+#              #
#    Updated: 2020/12/04 17:52:58 by aboutahr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME=minishell

FLAGS=-Wall -Wextra -Werror

SRC=	main.c 																	\
		shell_loop.c 															\
		memory_management/memory_management_func.c 								\
		memory_management/memory_management_helper.c							\
		helper_functions/check_syntax.c											\
		helper_functions/errors.c 												\
		helper_functions/ft_get_env_value.c 									\
		helper_functions/init.c 												\
		helper_functions/signals.c 												\
		helper_functions/ft_put.c 												\
		GNL/get_next_line.c														\
		GNL/get_next_line_utils.c												\
		builtins/functions/ft_append_redir.c									\
		builtins/functions/ft_cd.c												\
		builtins/functions/ft_echo.c											\
		builtins/functions/ft_exit.c											\
		builtins/functions/ft_export.c											\
		builtins/functions/ft_input_redir.c										\
		builtins/functions/ft_output_redir.c									\
		builtins/functions/ft_pwd.c												\
		builtins/functions/ft_unset.c											\
		builtins/functions/helper_functions/ft_redirections_helper.c			\
		builtins/functions/helper_functions/print_single_var.c					\
		line_parser/call_cmd.c													\
		line_parser/call_cmd_helper.c											\
		line_parser/linked_list_func.c											\
		line_parser/linked_list_func_helper.c									\
		line_parser/print_list.c												\
		line_parser/sort_cmd.c													\
		line_parser/treat_cmd.c													\
		line_parser/treat_line.c												\
		line_parser/treat_list.c												\
		line_parser/treat_single_command.c										\
		line_parser/get_args_after_redir.c										\
		line_parser/get_args_after_redir_helper.c								\
		line_parser/sort_redir.c												\
		line_parser/helper_functions/close_fd.c									\
		line_parser/helper_functions/get_args.c									\
		line_parser/helper_functions/get_args_helper.c							\
		line_parser/helper_functions/is_redirection.c							\
		line_parser/helper_functions/join_env_var.c								\
		line_parser/helper_functions/open_stdio.c								\
		line_parser/helper_functions/set_pipes.c								\
		line_parser/helper_functions/skip_shift_char.c							\
		execution/call_single_cmd.c												\
		execution/execute_cmd.c													\
		execution/fork_it.c														\
		execution/execute_builtins.c											\
		execution/exec_error.c													\
		libft/libft.a

all: $(NAME)

$(NAME):
	cd libft && make && cd ..
	gcc $(FLAGS) helper_functions/ft_put.c builtins/functions/ft_env.c libft/libft.a -o builtins/bin/env
	gcc $(FLAGS) $(SRC) -o $(NAME)

clean:
	cd libft && make clean && cd ..

fclean: clean
	cd libft && make fclean && cd ..
	rm -rf $(NAME)
	rm -rf builtins/bin/env

re : fclean all
