# include "../minishell.h"

void	call_commands_helper(t_piped_cmd *list, char ***envp, int pipe_index)
{
	int i;
	int fd;
	DIR	*directory;
	char *tmp;

	if (!list)
		return ;
	i = -1;
	if (pipe_index < g_pipes_count)
	{
		dup2(g_pipes_fd[pipe_index][1], 1);
		close(g_pipes_fd[pipe_index][1]);
	}
	if (!g_read_from_file && (pipe_index != 0 && pipe_index < g_pipes_count))
	{
		dup2(g_pipes_fd[pipe_index - 1][0], 0);
		close(g_pipes_fd[pipe_index - 1][0]);
	}
	if (!list->next && list->params[0][0] != '>')
	{
		dup2(g_stdio_fd[2], 2);
		dup2(g_stdio_fd[1], 1);
	}
	g_read_from_file = 0;
	g_next_cmd = (list->next) ? list->next->params[0] : NULL;
	if (THERE_IS_ERROR)
		return ;
	while (g_cmd_char[++i])
	{
		//printf("%s\n", g_cmd_char[i]);`
		if (!ft_strcmp(g_cmd_char[i], list->params[0]))
		{
			g_status = g_builtins[i](list->params + 1, envp);
			break;
		}
	}
	if (!g_cmd_char[i])
	{
		if (!(g_pid = fork()))
		{
			execve(list->params[0], list->params, (*envp));
			tmp = ft_strjoin("/bin/", list->params[0]);
			add_mem(tmp);
			execve(tmp, list->params, (*envp));
			if ((tmp = ft_strnstr(list->params[0], "/", ft_strlen(list->params[0]))) && (directory = opendir(list->params[0])))
			{
				FT_PUTSTR_ERR(list->params[0]);
				FT_PUTSTR_ERR(" : is a direcotory\n");
				closedir(directory);
				exit(0);
			}
			else
			{
				if (tmp)
				{
					FT_PUTSTR_ERR(list->params[0]);
					FT_PUTSTR_ERR(" : ");
					FT_PUTSTR_ERR(strerror(errno));
					FT_PUTSTR_ERR("\n");
				}
				else
				{
					FT_PUTSTR_ERR("Minishell : Command not found!\n");
				}
				exit(errno);
				
			}
		}
		else if (g_pid < 0)
		{
			FT_PUTSTR_ERR("Minishell: Fork Error\n");
			return ;
		}
		else
			wait(&g_status);
	}
	call_commands_helper(list->next, envp, ++pipe_index);
}

void	call_commands(t_cmd *list, char ***envp)
{
	int i;

	if (!list)
		return ;
	sort_cmd_for_redirections(&list->cmd, &list->cmd->next);
	g_pipes_count = list_cmd_size(list->cmd);
	if (g_pipes_count > 1)
		set_pipes();
	else
		g_pipes_count = 0;
	//printf("NB_PIPE = %d\n", g_pipes_count);
	call_commands_helper(list->cmd, envp, 0);
	if (!THERE_IS_ERROR)
		call_commands(list->next, envp);
}
