# include "../minishell.h"

void	print_cmd(t_piped_cmd *list)
{
	static int j = 1;
	int i;

	if (list)
	{
		i = -1;
		//printf("--------------------  FD = %d ------------------\n", list->fd);
		while (list->params[++i])
		{
			printf("   %i-- |%s|\n",j, list->params[i]);
			//printf("first CHAR = %d\n", list->params[i][0]);
		}
		j++;
		print_cmd(list->next);
	}
	j = 1;
}

void	print_list(t_cmd *list)
{
	if (list)
	{
		printf("%s\n", list->line);
		print_cmd(list->cmd);
		print_list(list->next);
	}
}
