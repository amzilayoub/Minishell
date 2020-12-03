/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <aboutahr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 12:03:37 by aboutahr            #+#    #+#             */
/*   Updated: 2020/11/21 19:06:52 by aboutahr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	call_commands_helper(t_piped_cmd *list, char ***envp, int *pipe_index)
{
	if (!list)
		return ;
	sort_cmd_for_redirections(
				&list->single_command,
				&list->single_command->next);
	call_single_command(list, list->single_command, envp, pipe_index);
	call_commands_helper(list->next, envp, pipe_index);
}

void	call_commands(t_cmd *list, char ***envp)
{
	int pipe_index;

	pipe_index = 0;
	g_is_piped = 0;
	if (!list)
		return ;
	g_pipes_count = list_cmd_size(list->cmd);
	if (g_pipes_count > 1)
		set_pipes();
	else
		g_pipes_count = 0;
	call_commands_helper(list->cmd, envp, &pipe_index);
	if (!THERE_IS_ERROR)
		call_commands(list->next, envp);
}
