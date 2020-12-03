/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <aboutahr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 12:38:22 by aboutahr            #+#    #+#             */
/*   Updated: 2020/11/21 18:57:08 by aboutahr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_commands_arg(t_single_command *list, char **envp)
{
	if (!list)
		return ;
	list->params = get_arg(list->line, envp);
	get_commands_arg(list->next, envp);
}

void	treat_cmd_helper(t_piped_cmd *list, char **envp)
{
	if (!list)
		return ;
	get_commands_arg(list->single_command, envp);
	treat_cmd_helper(list->next, envp);
}

void	treat_cmd(t_cmd *list, char **envp)
{
	if (!list)
		return ;
	treat_cmd_helper(list->cmd, envp);
	treat_cmd(list->next, envp);
}
