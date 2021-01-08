/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:38:53 by aamzil            #+#    #+#             */
/*   Updated: 2021/01/08 16:38:54 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_cmd(t_single_command *list, char ***envp, DIR *directory)
{
	int		n;

	n = execute_builtin(g_pipe_cmd, g_redirections, list, envp);
	if (g_pipes_count == 0 && n == 0)
	{
		if (execute_builtin(g_cmd_char, g_builtins, list, envp) == 0)
			fork_it(list, envp, directory, NULL);
		else if (g_is_exit && g_pipes_count == 0)
			return ;
		else
			g_is_exit = 0;
	}
	else if (n == 0)
		fork_it(list, envp, directory, &execute_builtin);
}
