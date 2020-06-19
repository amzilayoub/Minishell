# include "minishell.h"

void	free_cmd_array(void)
{
	int i;

	i = -1;
	//while (g_cmd_char[++i])
		//free(g_cmd_char[i]);
	//free(g_cmd_char);
	i = -1;
	//while (g_pipe_cmd[++i])
	//	free(g_pipe_cmd[i]);
	//free(g_pipe_cmd);
}

void	free_memory(t_mem_alloc **list,int flag)
{
	int i;

	i = -1;
	if (flag == FREE_EXIT_MODE)
		free_cmd_array();
	if (!(*list))
		return ;
	free_memory(&(*list)->next, flag);
	free((*list)->mem);
	(*list)->mem = NULL;
	free((*list));
	(*list) = NULL;
	while (++i < g_pipes_count && g_pipes_count > 1)
	{
		free(g_pipes_fd[i]);
		g_pipes_fd[i] = NULL;
	}
	free(g_pipes_fd);
	g_pipes_fd = NULL;
}

void	add_mem_helper(t_mem_alloc **list, void *mem)
{
	if ((*list))
		add_mem_helper(&(*list)->next, mem);
	else
	{
		(*list) = (t_mem_alloc*)malloc((sizeof(t_mem_alloc)));
		(*list)->mem = mem;
		(*list)->next = NULL;
	}
}

void	add_mem(void *mem)
{
	add_mem_helper(&g_mem_alloc, mem);
}
