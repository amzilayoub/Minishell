/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <aamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 11:05:59 by aamzil            #+#    #+#             */
/*   Updated: 2020/10/19 11:06:02 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_fd(void)
{
	int i;

	i = -1;
	while (++i < g_pipes_count && g_pipes_count > 1)
	{
		close(g_pipes_fd[i][0]);
		close(g_pipes_fd[i][1]);
	}
	open_stdio();
}
