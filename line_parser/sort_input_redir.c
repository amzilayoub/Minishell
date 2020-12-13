/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_output_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 17:56:11 by aamzil            #+#    #+#             */
/*   Updated: 2020/11/21 19:01:21 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// void	sort_input_redir_helper(t_piped_cmd *list)
// {
// 	char	*input;
// 	char	*tmp;
// 	char	*tmp2;
// 	int		first_part;

// 	if (!(input = ft_strchr(list->line, '<')))
// 		return ;
// 	first_part = input - list->line;
// 	tmp = ft_substr(list->line, 0, first_part);
// 	tmp2 = ft_strjoin(input, " ");
// 	add_mem(tmp2);
// 	add_mem(tmp);
// 	add_mem(list->line);
// 	list->line = ft_strjoin(tmp2, tmp);
// 	printf("LINE = %s\n", list->line);
// }

 
// void	sort_input_redir(t_cmd *list)
// {
// 	if (!list)
// 		return ;
// 	sort_input_redir_helper(list->cmd);
// 	sort_input_redir(list->next);
// }

t_single_command	*sort_input_redir_helper(t_single_command *list)
{
	t_single_command	*insert;
	t_single_command	*p1;
	t_single_command	*prev;
	int					i;

	i = 0;
	insert = list;
	prev = NULL;
	p1 = (list)->next;

	while ((insert) && (p1))
	{
		if ((p1)->params[0] && (p1)->params[0][0] == '<')
		{
			if (prev)
				(prev)->next = (insert)->next;
			(insert)->next = (p1)->next;
			(p1)->next = (insert);
			if (i == 0)
				(list) = (p1);
			i++;
			prev = p1;
			
			// insert = prev;
			// p1 = prev;
		}
		prev = p1;
		p1 = (p1)->next;
	}
	return (list);
}

void	sort_input_redir(t_piped_cmd *list)
{
	if (!list)
		return ;
	list->single_command = sort_input_redir_helper(list->single_command);
}

