/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:54:03 by aamzil            #+#    #+#             */
/*   Updated: 2021/01/06 12:54:10 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fork_it(t_single_command *list, char ***envp,
				DIR *directory,
				int (*fun)(char **cmd, int (*funs[])(char **args, char ***envp),
				t_single_command *list, char ***envp))
{
	char	*tmp;
	char	ret;

	if (!(g_pid = fork()))
	{
		if (fun != NULL && fun(g_cmd_char, g_builtins, list, envp) == 1)
			exit(g_status);
		ret = find_command(list->params, (*envp));
		tmp = ft_strnstr(list->params[0], "/", ft_strlen(list->params[0]));
		exit_syntax_error(list, directory, tmp, ret);
	}
	else if (g_pid < 0)
	{
		FT_PUTSTR_ERR("Minishell: Fork Error\n");
		return ;
	}
	else
		wait(&g_status);
}
