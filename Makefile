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

FLAGS=-g -Wall -Wextra -Werror

SRC= 	check_syntax.c										\
		errors.c 											\
		ft_get_env_value.c 									\
		init.c 												\
		main.c 												\
		memory_management_func.c 							\
		memory_management_helper.c							\
		shell_loop.c 										\
		GNL/get_next_line.c									\
		GNL/get_next_line_utils.c							\
		builtins/functions/ft_append_redir.c				\
		builtins/functions/ft_cd.c							\
		builtins/functions/ft_echo.c						\
		builtins/functions/ft_exit.c						\
		builtins/functions/ft_sort.c						\
		builtins/functions/ft_export.c						\
		builtins/functions/ft_input_redir.c					\
		builtins/functions/ft_output_redir.c				\
		builtins/functions/ft_pwd.c							\
		builtins/functions/ft_redirections_helper.c			\
		builtins/functions/ft_unset.c						\
		line_parser/call_cmd.c								\
		line_parser/call_cmd_helper.c						\
		line_parser/linked_list_func.c						\
		line_parser/linked_list_func_helper.c				\
		line_parser/print_list.c							\
		line_parser/sort_cmd.c								\
		line_parser/treat_cmd.c								\
		line_parser/treat_line.c							\
		line_parser/treat_list.c							\
		line_parser/treat_single_command.c					\
		line_parser/sort_output_redir.c						\
		line_parser/sort_input_redir.c						\
		line_parser/sort_output_redir_helper.c				\
		line_parser/helper_functions/close_fd.c				\
		line_parser/helper_functions/get_args.c				\
		line_parser/helper_functions/is_redirection.c		\
		line_parser/helper_functions/join_env_var.c			\
		line_parser/helper_functions/open_stdio.c			\
		line_parser/helper_functions/set_pipes.c			\
		line_parser/helper_functions/skip_shift_char.c		\
		libft/libft.a

all: $(NAME)

$(NAME):
	cd libft && make && cd ..
	gcc $(FLAGS) builtins/functions/ft_env.c libft/libft.a -o builtins/bin/env
	gcc $(FLAGS) $(SRC) -o $(NAME)

clean:
	cd libft && make clean && cd ..

fclean: clean
	cd libft && make fclean && cd ..
	rm -rf $(NAME)
	rm -rf builtins/bin/env

re : fclean all
