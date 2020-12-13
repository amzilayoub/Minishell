/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args_after_redir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 17:56:11 by aamzil            #+#    #+#             */
/*   Updated: 2020/11/21 19:01:21 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_args_after_redir(t_cmd *list)
{
	if (!list)
		return ;
	get_args_after_redir_helper(list->cmd);
	get_args_after_redir(list->next);
}
