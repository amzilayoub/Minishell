all:
	gcc -g *.c GNL/*.c builtins/*.c line_parser/*.c line_parser/helper_functions/*.c  libft.a
run: all
	./a.out
