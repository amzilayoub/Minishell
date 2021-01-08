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

char	is_numeric(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}

void	ft_exit_error(char **args, int is_number, int many_args)
{
	if (args && (*args) && !is_number)
	{
		FT_PUTSTR_ERR("Minishell: exit: numeric argument required\n");
		free_memory(&g_mem_alloc, FREE_EXIT_MODE);
		clear_cmd_list(&g_cmd_list);
		exit(255);
	}
	else if (many_args && is_number)
		FT_PUTSTR_ERR("Minishell: exit: too many arguments\n");
	else if (!many_args && is_number)
	{
		is_number = ft_atoi(args[0]);
		free_memory(&g_mem_alloc, FREE_EXIT_MODE);
		clear_cmd_list(&g_cmd_list);
		exit(is_number);
	}
	else
	{
		free_memory(&g_mem_alloc, FREE_EXIT_MODE);
		clear_cmd_list(&g_cmd_list);
		exit(0);
	}
}

int		ft_exit(char **args, char ***envp)
{
	int many_args;
	int is_number;

	(void)envp;
	close_fd();
	open_stdio();
	many_args = 0;
	is_number = 0;
	g_is_exit = 1;
	if (args && args[0])
	{
		is_number = is_numeric(args[0]);
		many_args += (args[1] != NULL);
	}
	ft_exit_error(args, is_number, many_args);
	return (1);
}
