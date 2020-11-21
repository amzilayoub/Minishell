/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <aamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 12:37:10 by aamzil            #+#    #+#             */
/*   Updated: 2020/11/21 18:58:01 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_single_command(t_single_command *list)
{
	int i;

	if (!list)
		return ;
	printf("----- |%s|\n", list->line);
	i = -1;
	while (list->params[++i])
	{
		printf("------- %i -> |%s|\n", i + 1, list->params[i]);
	}
	print_single_command(list->next);
}

void	print_cmd(t_piped_cmd *list)
{
	if (!list)
		return ;
	printf("-- |%s|\n", list->line);
	print_single_command(list->single_command);
	print_cmd(list->next);
}

void	print_list(t_cmd *list)
{
	if (list)
	{
		printf("|%s|\n", list->line);
		print_cmd(list->cmd);
		print_list(list->next);
	}
}
