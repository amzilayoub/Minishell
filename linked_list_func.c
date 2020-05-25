# include "minishell.h"

void	clear_cmd_list(t_cmd **list)
{
	if ((*list))
		clear_cmd_list(&(*list)->next);
	// free memory here
	//(*list)->line = NULL;
	//(*list)->cmd = NULL;
	(*list) = NULL;
}

int	list_cmd_size(t_piped_cmd *list)
{
	if (!list)
		return (0);
	//if (list->params[0][0] == '<')
		//return (list_cmd_size(list->next));
	return (1 + list_cmd_size(list->next));
}

void	add_cmd(t_piped_cmd **list, char *line)
{
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
	if ((*list))
		create_cmd_list(&((*list)->next), line);
	else
	{
		(*list) = (t_cmd*)malloc(sizeof(t_cmd));
		(*list)->line = line;
		(*list)->next = NULL;
	}
}
