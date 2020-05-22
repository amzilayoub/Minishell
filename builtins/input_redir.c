#include "../minishell.h"

void	ft_input_redir(char **args, char ***envp)
{
	int fd;

	if ((fd = open(args[0], O_RDONLY)) < 0)
	{
		write(2, "ERROR\n", ft_strlen("ERROR\n"));
		return ;
	}
	//write(2, args[0], ft_strlen(args[0]));
	//write(2, "|\n", 2);
	g_read_from_file = 1;
	dup2(fd, 0);
	close(fd);
	//printf("FILE =  %s\n", args[0]);
}
