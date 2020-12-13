/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <aamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 17:18:26 by aamzil            #+#    #+#             */
/*   Updated: 2020/10/19 13:18:00 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_exit(char **args, char ***envp)
{
	int i;

	(void)args;
	(void)envp;
	close_fd();
	open_stdio();
	FT_PUTSTR("exit\n");
	if (args && (*args) != NULL)
	{
		i = -1;
		while ((*args)[++i])
		{
			if (!ft_isdigit((*args)[i]))
			{
				print_cmd_with_error((*args),
					"Sorry but my exit works without arguments !");
				break ;
			}
		}
	}
	FT_PUTSTR_ERR("See you buddy !\n");
	free_memory(&g_mem_alloc, FREE_EXIT_MODE);
	clear_cmd_list(&g_cmd_list);
	exit(0);
	return (0);
}
