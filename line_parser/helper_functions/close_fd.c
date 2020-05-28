# include "../../minishell.h"

void	close_fd(void)
{
	int i;

	i = -1;
	while (++i < g_pipes_count && g_pipes_count > 1)
	{
		close(g_pipes_fd[i][0]);
		close(g_pipes_fd[i][1]);
	}
}
