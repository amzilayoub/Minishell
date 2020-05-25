#include "../minishell.h"

int	ft_input_redir(char **args, char ***envp)
{
	int fd;
	int i;

	i = 0;
	if (!(*args))
		return (set_error_print("bash : syntax error\n"));
		//error
	while (args[i])
		i++;
	if ((fd = open(args[i - 1], O_RDONLY)) < 0)
	{
		FT_PUTSTR_ERR("bash : can't open this File\n");
		return (1);
	}
	//write(2, args[0], ft_strlen(args[0]));
	//write(2, "|\n", 2);
	g_read_from_file = 1;
	dup2(fd, 0);
	close(fd);
	return (0);
	//printf("FILE =  %s\n", args[0]);
}
