# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aamzil <aamzil@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/19 13:04:45 by aamzil            #+#    #+#              #
#    Updated: 2020/10/19 13:08:21 by aamzil           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME=Minishell

SRC = *.c GNL/*.c builtins/*.c line_parser/*.c line_parser/helper_functions/*.c  libft.a

all: $(NAME)

$(NAME):
	gcc -Wall -Wextra -Werror $(SRC) -o Minishell

clean:
	rm -rf Minishell

fclean: clean

re : fclean all