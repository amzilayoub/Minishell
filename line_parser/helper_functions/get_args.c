/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <aamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 11:06:24 by aamzil            #+#    #+#             */
/*   Updated: 2020/11/21 19:00:35 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**get_arg(char *line, char ***envp)
{
	char		**args;
	char		*tmp;
	t_arg_manip	vars;

	vars.i = -1;
	vars.start = 0;
	vars.j = -1;
	vars.space = 0;
	args = (char**)malloc(sizeof(char*) * (get_arg_len(line) + 1));
	vars.quote = 0;
	get_arg_helper(&vars, &line, envp, &args);
	if ((tmp = ft_substr(line, vars.start, vars.i - vars.start))[0])
		args[++vars.j] = tmp;
	else
		add_mem(tmp);
	args[++vars.j] = NULL;
	vars.i = -1;
	if (!args[0])
	{
		args[0] = ft_strdup("");
		args[1] = NULL;
	}
	return (args);
}
