#include "minishell.h"

int	prompt(void)
{
	return (write(1, "$ ", 2));
}

void	ft_sigint(int num)
{
	//send signal to the children of fork
	FT_PUTSTR("\n$ ");
}

void	shell_loop(char **envp)
{
	char *line;

	//manage those signals
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_sigint);
	while (prompt() && get_next_line(0, &line) > 0)
	{
		add_mem(line);
		if ((check_semicolons(line)))
		{
			FT_PUTSTR_ERR(ERROR_MSG);
			continue;
		}
		treat_line(line);
		treat_list(g_cmd_list);
		if (THERE_IS_ERROR)
		{
			FT_PUTSTR_ERR(ERROR_MSG);
			//print_list(g_cmd_list);
			continue;
		}
		treat_cmd(g_cmd_list, envp);
		call_commands(g_cmd_list, &envp);
		close_fd();
		open_stdio();
		clear_cmd_list(&g_cmd_list);
		free_memory(&g_mem_alloc, FREE_MODE);
		//printf("--------------------------FINISH--------------------\n");
				//print_list(g_cmd_list);

	}
}
