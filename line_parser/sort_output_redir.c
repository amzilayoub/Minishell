/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_output_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 17:56:11 by aboutahr            #+#    #+#             */
/*   Updated: 2020/11/21 19:01:21 by aboutahr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sort_output_redir(t_cmd *list)
{
	if (!list)
		return ;
	sort_output_redir_helper(list->cmd);
	sort_output_redir(list->next);
}
