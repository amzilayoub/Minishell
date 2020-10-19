/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <aamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 12:03:37 by aamzil            #+#    #+#             */
/*   Updated: 2020/10/19 13:20:50 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	find_command(char **params, char **envp)
{
	char	**bin_path;
	char	*path;
	int		i;

	execve(params[0], params, envp);
	i = -1;
	path = ft_get_env_value("$PATH", envp);
	bin_path = ft_split(path, ':');
	free(path);
	path = params[0];
	while (bin_path[++i])
	{
		add_mem(bin_path);
		bin_path[i] = ft_strjoin(bin_path[i], "/");
		add_mem(bin_path);
	}
	add_mem(bin_path);
	i = -1;
	while (bin_path[++i])
	{
		path = ft_strjoin(bin_path[i], params[0]);
		add_mem(path);
		execve(path, params, envp);
	}
}

void	open_pipes(t_piped_cmd *list, int pipe_index)
{
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
}

void	fork_it(t_piped_cmd *list, char ***envp, DIR *directory)
{
	char *tmp;

	if (!(g_pid = fork()))
	{
		find_command(list->params, (*envp));
		tmp = ft_strnstr(list->params[0], "/", ft_strlen(list->params[0]));
		if ((directory = opendir(list->params[0])) && tmp)
		{
			print_cmd_with_error(list->params[0], "is a direcotory");
			closedir(directory);
			exit(0);
		}
		else if (tmp)
			print_cmd_with_error(list->params[0], strerror(errno));
		else
			print_cmd_with_error(list->params[0], "Command not found!");
		exit(errno);
	}
	else if (g_pid < 0)
	{
		FT_PUTSTR_ERR("Minishell: Fork Error\n");
		return ;
	}
	else
		wait(&g_status);
}

void	call_commands_helper(t_piped_cmd *list, char ***envp, int pipe_index)
{
	int		i;
	DIR		*directory;

	directory = NULL;
	if (!list)
		return ;
	i = -1;
	open_pipes(list, pipe_index);
	g_next_cmd = (list->next) ? list->next->params[0] : NULL;
	if (THERE_IS_ERROR)
		return ;
	while (g_cmd_char[++i])
	{
		if (!ft_strcmp(g_cmd_char[i], list->params[0]))
		{
			g_status = g_builtins[i](list->params + 1, envp);
			break ;
		}
	}
	if (!g_cmd_char[i])
		fork_it(list, envp, directory);
	call_commands_helper(list->next, envp, ++pipe_index);
}

void	call_commands(t_cmd *list, char ***envp)
{
	if (!list)
		return ;
	sort_cmd_for_redirections(&list->cmd, &list->cmd->next);
	g_pipes_count = list_cmd_size(list->cmd);
	if (g_pipes_count > 1)
		set_pipes();
	else
		g_pipes_count = 0;
	call_commands_helper(list->cmd, envp, 0);
	if (!THERE_IS_ERROR)
		call_commands(list->next, envp);
}
