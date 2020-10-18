/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <aamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 17:18:26 by aamzil            #+#    #+#             */
/*   Updated: 2020/10/18 19:08:44 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit(char **args, char ***envp)
{
	free_memory(&g_mem_alloc, FREE_EXIT_MODE);
	close_fd();
	open_stdio();
	clear_cmd_list(&g_cmd_list);
	exit(0);
	return (0);
}
