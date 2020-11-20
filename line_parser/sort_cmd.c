/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <aamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 12:38:11 by aamzil            #+#    #+#             */
/*   Updated: 2020/10/19 12:38:12 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sort_cmd_for_redirections(t_single_command **current, t_single_command **next)
{
	char **tmp;

	if (!(*current) || !(*next))
		return ;
	if ((*next)->params[0][0] == '<')
	{
		// if ((*current)->params[0][0] == '>')
		// 	(*next) = (*next)->next;
		// else
		// {
			tmp = (*current)->params;
			(*current)->params = (*next)->params;
			(*next)->params = tmp;
		// }
	}
	sort_cmd_for_redirections(next, &(*next)->next);
}
