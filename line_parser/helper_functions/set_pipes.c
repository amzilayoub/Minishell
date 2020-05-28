# include "../../minishell.h"

void	set_pipes(void)
{
	int i;

	g_pipes_fd = (int**)malloc(sizeof(int*) * g_pipes_count);
	i = -1;
	while (++i < g_pipes_count)
	{
		g_pipes_fd[i] = (int*)malloc(sizeof(int) * 2);
		pipe(g_pipes_fd[i]);
	}
}
