/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <aboutahr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 12:02:50 by aboutahr            #+#    #+#             */
/*   Updated: 2020/10/19 12:02:54 by aboutahr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	set_pipes(void)
{
	int i;

	g_pipes_fd = (int**)malloc(sizeof(int*) * g_pipes_count);
	i = -1;
	while (++i < g_pipes_count)
	{
		g_pipes_fd[i] = (int*)malloc(sizeof(int) * 2);
		pipe(g_pipes_fd[i]);
	}
}
