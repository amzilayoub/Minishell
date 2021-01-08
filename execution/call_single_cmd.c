/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:38:07 by aamzil            #+#    #+#             */
/*   Updated: 2021/01/08 16:38:19 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	call_single_command(
			t_piped_cmd *parent,
			t_single_command *list,
			char ***envp,
			int *pipe_index)
{
	DIR		*directory;

	if (THERE_IS_ERROR)
	{
		THERE_IS_ERROR = 0;
		return ;
	}
	if (!list || g_is_exit)
		return ;
	directory = NULL;
	open_pipes(parent, list, (*pipe_index));
	g_next_cmd = (list->next) ? list->next->params[0] : NULL;
	g_there_is_error = 0;
	g_error_n = 0;
	g_builtin_error = 0;
	g_status = 0;
	list->cmd_lowercase = get_lowercase(list->params[0]);
	execute_cmd(list, envp, directory);
	(*pipe_index)++;
	call_single_command(parent, list->next, envp, pipe_index);
}
