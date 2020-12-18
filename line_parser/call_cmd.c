/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <aamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 12:03:37 by aamzil            #+#    #+#             */
/*   Updated: 2020/11/21 19:06:52 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	call_commands_helper(t_piped_cmd *list, char ***envp, int *pipe_index)
{
	if (!list)
		return ;
	// sort_cmd_for_redirections(
	// 			&list->single_command,
	// 			&list->single_command->next);
	if (list->single_command && list->single_command->params[0] && list->single_command->params[0][0] == '>')
		g_input_read = 0;
	else
		g_input_read = 1;
	call_single_command(list, list->single_command, envp, pipe_index);
	call_commands_helper(list->next, envp, pipe_index);
}

void	call_commands(t_piped_cmd *list, char ***envp)
{
	int pipe_index;

	pipe_index = 0;
	g_is_piped = 0;
	if (!list)
		return ;
	g_pipes_count = list_cmd_size(list);
	if (g_pipes_count > 1)
		set_pipes();
	else
		g_pipes_count = 0;
	call_commands_helper(list, envp, &pipe_index);
}