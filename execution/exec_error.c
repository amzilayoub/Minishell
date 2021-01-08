/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:38:30 by aamzil            #+#    #+#             */
/*   Updated: 2021/01/08 16:38:31 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_error(t_single_command *list, DIR *directory, char ret, char *tmp)
{
	if ((directory = opendir(list->params[0])) && tmp)
	{
		print_cmd_with_error(list->params[0], "is a direcotory");
		closedir(directory);
		exit(126);
	}
	else if (!tmp && !ret)
	{
		print_cmd_with_error(list->params[0], "command not found !");
		exit(127);
	}
	else
		print_cmd_with_error(list->params[0], strerror(errno));
	exit(errno);
}
