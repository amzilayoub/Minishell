/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_func_helper.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 19:01:45 by aboutahr            #+#    #+#             */
/*   Updated: 2020/11/21 19:02:01 by aboutahr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_single_command(t_single_command **list)
{
	int i;

	if (!(*list))
		return ;
	i = -1;
	clear_single_command(&(*list)->next);
	free((*list)->line);
	(*list)->line = NULL;
	while ((*list)->params[++i])
	{
		free((*list)->params[i]);
		(*list)->params[i] = NULL;
	}
	free((*list)->params);
	free((*list));
	(*list) = NULL;
}

void	clear_cmd_list_helper(t_piped_cmd **list)
{
	if (!(*list))
		return ;
	clear_single_command(&((*list)->single_command));
	clear_cmd_list_helper(&(*list)->next);
	free((*list)->line);
	(*list)->line = NULL;
	free((*list));
	(*list) = NULL;
}

void	clear_cmd_list(t_cmd **list)
{
	if (!(*list))
		return ;
	clear_cmd_list(&(*list)->next);
	clear_cmd_list_helper(&(*list)->cmd);
	free((*list)->line);
	(*list)->line = NULL;
	free((*list));
	(*list) = NULL;
}
