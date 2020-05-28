# include "../minishell.h"

void	treat_list(t_cmd *cmd_list)
{
	int i;
	int j;
	int start;
	char *tmp;

	if (!cmd_list)
		return ;
	if (check_pipes_error(&cmd_list->line))
		return ;
	i = -1;
	start = 0;
	while (cmd_list->line[++i])
	{
		if (cmd_list->line[i] == '\\')
		{
			i++;
			continue;
		}
		j = -1;
		while (g_pipe_cmd[++j])
		{
			if (g_pipe_cmd[j][0] == cmd_list->line[i])
			{
				add_cmd(&cmd_list->cmd, ft_substr(cmd_list->line, start, i - start));
				start = i + is_redirection(g_pipe_cmd[j], cmd_list->line + i)/* + skip_char(cmd_list->line + i + 1, ' ')*/;
				i += (!ft_strncmp(cmd_list->line + i, ">>", 2));
				break;
			}
		}
	}
	add_cmd(&cmd_list->cmd, ft_substr(cmd_list->line, start, i - start + 1));
	treat_list(cmd_list->next);
}
