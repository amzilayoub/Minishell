# include "../minishell.h"

void	sort_cmd_for_redirections(t_piped_cmd **current, t_piped_cmd **next)
{
	char **tmp;

	//printf("CUR = %s\n", (*current)->params[0]);
	if (!(*current) || !(*next))
		return ;
	if ((*next)->params[0][0] == '<')
	{
		if ((*current)->params[0][0] == '>')
			(*next) = (*next)->next;
		else
		{
			tmp = (*current)->params;
			(*current)->params = (*next)->params;
			(*next)->params = tmp;
		}
	}
	sort_cmd_for_redirections(next, &(*next)->next);
}
