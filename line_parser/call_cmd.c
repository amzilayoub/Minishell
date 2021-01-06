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

char	*get_lowercase(char *str)
{
	char	*lower;
	int		i;

	if (str == NULL)
		return (NULL);
	lower = ft_strdup(str);
	if (!ft_strcmp(str, "EXIT"))
		return (lower);
	i = -1;
	while (lower[++i])
		lower[i] = ft_tolower(lower[i]);
	return (lower);
}

void	execute_command(t_single_command *list, char ***envp)
{
	int		n;
	DIR		*directory;

	directory = NULL;
	n = execute_builtin(g_pipe_cmd, g_redirections, list, envp);
	if (g_pipes_count == 0 && n == 0)
	{
		if (execute_builtin(g_cmd_char, g_builtins, list, envp) == 0)
			fork_it(list, envp, directory, NULL);
		else if (g_is_exit && g_pipes_count == 0)
			return ;
		else
			g_is_exit = 0;
	}
	else if (n == 0)
		fork_it(list, envp, directory, &execute_builtin);
}

void	call_single_command(
			t_piped_cmd *parent,
			t_single_command *list,
			char ***envp,
			int *pipe_index)
{
	if (THERE_IS_ERROR)
	{
		THERE_IS_ERROR = 0;
		return ;
	}
	if (!list || g_is_exit)
		return ;
	open_pipes(parent, list, (*pipe_index));
	g_next_cmd = (list->next) ? list->next->params[0] : NULL;
	g_there_is_error = 0;
	g_error_n = 0;
	g_builtin_error = 0;
	g_status = 0;
	list->cmd_lowercase = get_lowercase(list->params[0]);
	execute_command(list, envp);
	(*pipe_index)++;
	call_single_command(parent, list->next, envp, pipe_index);
}

void	call_commands_helper(t_piped_cmd *list, char ***envp, int *pipe_index)
{
	if (!list)
		return ;
	if (list->single_command &&
		list->single_command->params[0] &&
		list->single_command->params[0][0] == '>')
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
