all:
	gcc -g *.c GNL/*.c builtins/*.c  libft.a
run: all
	./a.out
