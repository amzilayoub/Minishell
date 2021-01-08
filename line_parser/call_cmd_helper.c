/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_cmd_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 19:08:12 by aamzil            #+#    #+#             */
/*   Updated: 2020/11/21 19:12:26 by aamzil           ###   ########.fr       */
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

char	find_command(char **params, char **envp)
{
	char	**bin_path;
	char	*path;
	int		i;

	execve(params[0], params, envp);
	path = ft_get_env_value("$PATH", envp);
	if (!path)
		return (1);
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
	return (0);
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
