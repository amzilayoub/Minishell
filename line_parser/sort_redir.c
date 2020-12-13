/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_redir.c   		                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 17:56:11 by aamzil            #+#    #+#             */
/*   Updated: 2020/11/21 19:01:21 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


t_single_command	*swap_redirection(t_single_command *list)
{
	t_single_command	*pointer;
	t_single_command	*prev;
	char				is_swap;

	is_swap = 1;
	while (is_swap)
	{
		is_swap = 0;
		pointer = list;
		prev = NULL;
		while (pointer && pointer->next)
		{
			if (pointer->params[0] && pointer->next->params[0])
			{
				if (pointer->params[0][0] == '>' && pointer->next->params[0][0] == '<')
				{
					if (prev)
					{
						prev->next = pointer->next;
						pointer->next = pointer->next->next;
						prev->next->next = pointer;
					}
					else
					{
						prev = pointer->next;
						pointer->next = pointer->next->next;
						prev->next = pointer;
						list = prev;
					}
					is_swap = 1;
					break ;
				}
			}
			prev = pointer;
			pointer = pointer->next;
		}
	}
	return (list);
}


t_single_command	*sort_input_redir(t_single_command *list)
{
	t_single_command *prev;
	t_single_command *start;
	t_single_command *end;

	start = list;
	end =  NULL;
	prev = NULL;
	while (start)
	{
		if (start->params[0] && start->params[0][0] == '<')
		{
			end = start;
			break ;
		}
		prev = start;
		start = start->next;
	}
	while (end && end->next)
	{
		if (end->next->params[0] && end->next->params[0][0] != '<')
			break ;
		end = end->next;
	}
	if (!prev || !end)
		return (list);
	prev->next = end->next;
	end->next = prev;
	list = start;
	return (list);













	// t_single_command	*insert;
	// t_single_command	*p1;
	// t_single_command	*prev;
	// int					i;

	// i = 0;
	// insert = list;
	// prev = NULL;
	// p1 = (list)->next;

	// while ((insert) && (p1))
	// {
	// 	if ((p1)->params[0] && (p1)->params[0][0] == '<')
	// 	{
	// 		if (prev)
	// 			(prev)->next = (insert)->next;
	// 		(insert)->next = (p1)->next;
	// 		(p1)->next = (insert);
	// 		if (i == 0)
	// 			(list) = (p1);
	// 		i++;
	// 		prev = p1;
	// 		p1 = insert->next;
	// 	}
	// 	else
	// 	{
	// 		prev = p1;
	// 		p1 = (p1)->next;
	// 	}
	// }
	// return (list);
}

void	sort_redir(t_piped_cmd *list)
{
	if (!list)
		return ;
	list->single_command = swap_redirection(list->single_command);
	list->single_command = sort_input_redir(list->single_command);
	sort_redir(list->next);
}

