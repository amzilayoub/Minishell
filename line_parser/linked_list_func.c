# include "../minishell.h"

void	clear_cmd_list_helper(t_piped_cmd **list)
{
	int i;

	i = -1;
	if (!(*list))
		return ;
	clear_cmd_list_helper(&(*list)->next);
	free((*list)->line);
	(*list)->line = NULL;
	while ((*list)->params[++i])
	{
		free((*list)->params[i]);
		(*list)->params[i] = NULL;
	}
	free((*list)->params);
	free((*list));
	(*list) = NULL;
}

void	clear_cmd_list(t_cmd **list)
{
	if (!(*list))
		return ;
	clear_cmd_list(&(*list)->next);
	clear_cmd_list_helper(&(*list)->cmd);
	free((*list)->line);
	(*list)->line = NULL;
	free((*list));
	(*list) = NULL;
}

int	list_cmd_size(t_piped_cmd *list)
{
	if (!list)
		return (0);
	return (1 + list_cmd_size(list->next));
}

void	add_cmd(t_piped_cmd **list, char *line)
{
	if (!(*line))
	{
		add_mem(line);
		return ;
	}
	if ((*list))
		add_cmd(&((*list)->next), line);	
	else
	{
		(*list) = (t_piped_cmd*)malloc(sizeof(t_piped_cmd));
		(*list)->line = line;
		(*list)->next = NULL;
	}
}

void	create_cmd_list(t_cmd **list, char *line)
{
	if (!(*line))
	{
		add_mem(line);
		return ;
	}
	if ((*list))
		create_cmd_list(&((*list)->next), line);
	else if ((*line))
	{
		(*list) = (t_cmd*)malloc(sizeof(t_cmd));
		(*list)->line = line;
		(*list)->cmd = NULL;
		(*list)->next = NULL;
	}
}
