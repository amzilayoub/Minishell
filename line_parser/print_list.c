/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <aamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 12:37:10 by aamzil            #+#    #+#             */
/*   Updated: 2020/10/19 12:37:59 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_cmd(t_piped_cmd *list)
{
	static int	j = 1;
	int			i;

	if (list)
	{
		i = -1;
		while (list->params[++i])
			printf("   %i-- |%s|\n", j, list->params[i]);
		j++;
		print_cmd(list->next);
	}
}

void	print_list(t_cmd *list)
{
	if (list)
	{
		printf("%s\n", list->line);
		print_cmd(list->cmd);
		print_list(list->next);
	}
}
