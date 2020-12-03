/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_cmd_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 19:08:12 by aboutahr            #+#    #+#             */
/*   Updated: 2020/11/21 19:12:26 by aboutahr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	concat_command(char **bin_path, char **params, char **envp)
{
	int		i;
	char	*path;

	i = -1;
	while (bin_path[++i])
	{
		path = ft_strjoin(bin_path[i], params[0]);
		add_mem(path);
		execve(path, params, envp);
	}
}

void	find_command(char **params, char **envp)
{
	char	**bin_path;
	char	*path;
	int		i;

	execve(params[0], params, envp);
	path = ft_get_env_value("$PATH", envp);
	if (!path)
		return ;
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
	concat_command(bin_path, params, envp);
}

void	open_pipes(
			t_piped_cmd *parent_cmd,
			t_single_command *list,
			int pipe_index)
{
	if (pipe_index < g_pipes_count)
	{
		g_is_piped = 0;
		dup2(g_pipes_fd[pipe_index][1], 1);
		close(g_pipes_fd[pipe_index][1]);
	}
	if (!g_read_from_file && (pipe_index != 0 && pipe_index < g_pipes_count))
	{
		g_is_piped = 1;
		dup2(g_pipes_fd[pipe_index - 1][0], 0);
		close(g_pipes_fd[pipe_index - 1][0]);
	}
	if (!parent_cmd->next && !list->next && list->params[0][0] != '>')
	{
		dup2(g_stdio_fd[2], 2);
		dup2(g_stdio_fd[1], 1);
	}
	g_read_from_file = 0;
}

void	fork_it(t_single_command *list, char ***envp, DIR *directory)
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
		else if (!tmp)
			print_cmd_with_error(list->params[0], "command not found !");
		else
			print_cmd_with_error(list->params[0], strerror(errno));
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

void	call_single_command(
			t_piped_cmd *parent,
			t_single_command *list,
			char ***envp,
			int *pipe_index)
{
	DIR		*directory;
	int		i;

	if (!list)
		return ;
	directory = NULL;
	i = -1;
	open_pipes(parent, list, (*pipe_index));
	g_next_cmd = (list->next) ? list->next->params[0] : NULL;
	if (!g_next_cmd && parent->next)
		g_next_cmd = parent->next->single_command->params[0];
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
	if (!g_cmd_char[i] && list->params[0][0])
		fork_it(list, envp, directory);
	(*pipe_index)++;
	call_single_command(parent, list->next, envp, pipe_index);
}
