/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:45:58 by aamzil            #+#    #+#             */
/*   Updated: 2021/01/08 15:46:08 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int					swap_redirection_helper(t_single_command **list,
											t_single_command **pointer,
											t_single_command **prev,
											char *is_swap)
{
	if ((*pointer)->params[0] && (*pointer)->next->params[0])
	{
		if ((*pointer)->params[0][0] == '>' &&
			(*pointer)->next->params[0][0] == '<')
		{
			if ((*prev))
			{
				(*prev)->next = (*pointer)->next;
				(*pointer)->next = (*pointer)->next->next;
				(*prev)->next->next = (*pointer);
			}
			else
			{
				(*prev) = (*pointer)->next;
				(*pointer)->next = (*pointer)->next->next;
				(*prev)->next = (*pointer);
				(*list) = (*prev);
			}
			(*is_swap) = 1;
			return (1);
		}
	}
	return (0);
}

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
			if (swap_redirection_helper(&list, &pointer, &prev, &is_swap))
				break ;
			prev = pointer;
			pointer = pointer->next;
		}
	}
	return (list);
}

void				sort_input_redir_helper(t_single_command **prev,
											t_single_command **start,
											t_single_command **end)
{
	while ((*start))
	{
		if ((*start)->params[0] && (*start)->params[0][0] == '<')
		{
			(*end) = (*start);
			break ;
		}
		(*prev) = (*start);
		(*start) = (*start)->next;
	}
}

t_single_command	*sort_input_redir(t_single_command *list)
{
	t_single_command *prev;
	t_single_command *start;
	t_single_command *end;

	start = list;
	end = NULL;
	prev = NULL;
	sort_input_redir_helper(&prev, &start, &end);
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
}

void				sort_redir(t_piped_cmd *list)
{
	if (!list)
		return ;
	list->single_command = swap_redirection(list->single_command);
	list->single_command = sort_input_redir(list->single_command);
	sort_redir(list->next);
}
