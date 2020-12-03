/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management_func.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <aboutahr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 12:49:34 by aboutahr            #+#    #+#             */
/*   Updated: 2020/10/31 10:43:00 by aboutahr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(void)
{
	int i;

	i = -1;
	while (g_cmd_char[++i])
		free(g_cmd_char[i]);
	free(g_cmd_char);
	i = -1;
	while (g_pipe_cmd[++i])
		free(g_pipe_cmd[i]);
	free(g_pipe_cmd);
	if (g_first_dup_env)
	{
		i = -1;
		while (g_envp[++i])
			free(g_envp[i]);
		free(g_envp);
	}
}

void	free_cmd_array(t_mem_alloc *list)
{
	if (!list)
		return ;
	free_cmd_array(list->next);
	free(list->mem);
	free(list);
}

void	free_pipe(void)
{
	int i;

	if (g_pipes_count == -1)
		return ;
	i = -1;
	while (++i < g_pipes_count && g_pipes_count > 1)
	{
		free(g_pipes_fd[i]);
		g_pipes_fd[i] = NULL;
	}
	free(g_pipes_fd);
	g_pipes_fd = NULL;
	g_pipes_count = -1;
}

void	free_memory(t_mem_alloc **list, int flag)
{
	if (flag == FREE_EXIT_MODE)
	{
		free_all();
		free_cmd_array(g_mem_perma);
	}
	if (!(*list))
		return ;
	free_memory(&(*list)->next, FREE_MODE);
	free((*list)->mem);
	(*list)->mem = NULL;
	free((*list));
	(*list) = NULL;
	free_pipe();
}
