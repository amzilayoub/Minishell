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
