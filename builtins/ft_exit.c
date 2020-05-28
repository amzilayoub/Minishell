# include "../minishell.h"


int	ft_exit(char **args, char ***envp)
{
	//free all memory
	free_memory(&g_mem_alloc ,FREE_EXIT_MODE);
	close_fd();
	open_stdio();
	clear_cmd_list(&g_cmd_list);
	exit(0);
	return (0);
}
