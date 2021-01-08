/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:45:41 by aamzil            #+#    #+#             */
/*   Updated: 2021/01/08 16:45:47 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_sigint(int num)
{
	(void)num;
	if (g_line != NULL)
	{
		g_line = NULL;
	}
	ft_putstr("\n$ ");
}

void	ft_sigquit(int num)
{
	(void)num;
	return ;
}
