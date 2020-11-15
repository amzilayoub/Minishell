/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <aamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 12:38:22 by aamzil            #+#    #+#             */
/*   Updated: 2020/10/19 12:38:24 by aamzil           ###   ########.fr       */
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
