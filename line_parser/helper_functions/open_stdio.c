# include "../../minishell.h"

void	open_stdio(void)
{
	dup2(g_stdio_fd[0], 0);
	dup2(g_stdio_fd[1], 1);
	dup2(g_stdio_fd[2], 2);
}
