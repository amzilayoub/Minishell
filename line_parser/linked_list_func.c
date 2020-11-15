/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <aamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 12:36:36 by aamzil            #+#    #+#             */
/*   Updated: 2020/10/19 12:36:59 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_cmd_list_helper(t_piped_cmd **list)
{
	int i;

	i = -1;
	if (!(*list))
		return ;
	clear_cmd_list_helper(&(*list)->next);
	free((*list)->line);
	(*list)->line = NULL;
	// while ((*list)->params[++i])
	// {
	// 	free((*list)->params[i]);
	// 	(*list)->params[i] = NULL;
	// }
	// free((*list)->params);
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

int		list_cmd_size_helper(t_single_command *list)
{
	if (!list)
		return (0);
	return (1 + list_cmd_size_helper(list->next));
}

int		list_cmd_size(t_piped_cmd *list)
{
	if (!list)
		return (0);
	return (list_cmd_size_helper(list->single_command) + list_cmd_size(list->next));
}

void	add_cmd(t_piped_cmd **list, char *line)
{
	if (!(*line))
	{
		add_mem(line);
		return ;
	}
	if ((*list))
		add_cmd(&((*list)->next), line);
	else
	{
		(*list) = (t_piped_cmd*)malloc(sizeof(t_piped_cmd));
		(*list)->line = line;
		(*list)->single_command = NULL;
		(*list)->next = NULL;
	}
}


void	add_single_command(t_single_command **list, char *line)
{
	if (!(*line))
	{
		add_mem(line);
		return ;
	}
	if ((*list))
		add_single_command(&((*list)->next), line);
	else
	{
		(*list) = (t_single_command*)malloc(sizeof(t_single_command));
		(*list)->line = line;
		(*list)->params = NULL;
		(*list)->next = NULL;
	}
}

void	create_cmd_list(t_cmd **list, char *line)
{
	if (!(*line))
	{
		add_mem(line);
		return ;
	}
	if ((*list))
		create_cmd_list(&((*list)->next), line);
	else if ((*line))
	{
		(*list) = (t_cmd*)malloc(sizeof(t_cmd));
		(*list)->line = line;
		(*list)->cmd = NULL;
		(*list)->next = NULL;
	}
}
