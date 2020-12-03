# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aboutahr <aboutahr@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/19 13:04:45 by aboutahr            #+#    #+#              #
#    Updated: 2020/11/09 18:00:54 by aboutahr           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME=minishell

FLAGS=-Wall -Wextra -Werror

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
		builtins/ft_append_redir.c							\
		builtins/ft_cd.c									\
		builtins/ft_echo.c									\
		builtins/ft_env.c									\
		builtins/ft_exit.c									\
		builtins/ft_export.c								\
		builtins/ft_input_redir.c							\
		builtins/ft_output_redir.c							\
		builtins/ft_pwd.c									\
		builtins/ft_redirections_helper.c					\
		builtins/ft_unset.c									\
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
	gcc $(FLAGS) $(SRC) -o $(NAME)

clean:
	cd libft && make clean && cd ..

fclean: clean
	cd libft && make fclean && cd ..
	rm -rf $(NAME)

re : fclean all
