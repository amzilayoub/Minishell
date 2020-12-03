/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <aboutahr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 12:38:11 by aboutahr            #+#    #+#             */
/*   Updated: 2020/10/19 12:38:12 by aboutahr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	if ((*current)->params[0][0] == '>')
**		(*next) = (*next)->next;
**	else
**	{
*/

void	sort_cmd_for_redirections(t_single_command **current,
									t_single_command **next)
{
	char **tmp;

	if (!(*current) || !(*next))
		return ;
	if ((*next)->params[0][0] == '<')
	{
		tmp = (*current)->params;
		(*current)->params = (*next)->params;
		(*next)->params = tmp;
	}
	sort_cmd_for_redirections(next, &(*next)->next);
}
