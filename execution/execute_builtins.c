/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:38:43 by aamzil            #+#    #+#             */
/*   Updated: 2021/01/08 16:38:44 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		execute_builtin(char **cmd,
						int (*funs[])(char **args, char ***envp),
						t_single_command *list,
						char ***envp)
{
	int i;

	i = -1;
	while (cmd[++i])
	{
		if (!ft_strcmp(cmd[i], list->cmd_lowercase))
		{
			g_status = funs[i](list->params + 1, envp);
			g_builtin_error = g_status;
			return (1);
		}
	}
	return (0);
}
