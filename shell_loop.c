/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <aamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 16:17:47 by aamzil            #+#    #+#             */
/*   Updated: 2020/10/27 18:47:08 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		prompt(void)
{
	return (write(1, "$ ", 2));
}

void	ft_sigint(int num)
{
	(void)num;
	FT_PUTSTR("\n$ ");
}

/*
** To see the commands with their parmams,
** add this line print_list(g_cmd_list)
** before close_fd() function
*/

char	*read_line(void)
{
	char	*tmp;
	char	*line;
	int		n;

	tmp = ft_strdup("");
	add_mem(tmp);
	line = NULL;
	while ((n = get_next_line(0, &tmp)) >= 0)
	{
		line = (line) ? ft_strjoin(line, tmp) : tmp;
		add_mem(line);
		if (n > 0)
			break ;
		else if (n == 0 && !(*tmp) && !(*line))
			ft_exit(NULL, NULL);
	}
	return (line);
}

void	shell_loop(char **envp)
{
	char	*line;

	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_sigint);
	while (prompt())
	{
		line = read_line();
		if (check_semicolons(line))
		{
			FT_PUTSTR_ERR(ERROR_MSG);
			continue;
		}
		treat_line(line);
		treat_list(g_cmd_list);
		if (THERE_IS_ERROR)
		{
			FT_PUTSTR_ERR(ERROR_MSG);
			continue;
		}
		treat_cmd(g_cmd_list, envp);
		call_commands(g_cmd_list, &envp);
		close_fd();
		clear_cmd_list(&g_cmd_list);
		free_memory(&g_mem_alloc, FREE_MODE);
	}
}
