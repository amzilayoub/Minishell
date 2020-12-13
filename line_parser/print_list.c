/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <aboutahr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 12:37:10 by aamzil            #+#    #+#             */
/*   Updated: 2020/12/07 17:21:08 by aboutahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_single_command(t_single_command *list)
{
	int i;

	if (!list)
		return ;
	FT_PUTSTR("----- |\n");
	FT_PUTSTR(list->line);
	FT_PUTSTR("|\n");
	i = -1;
	while (list->params[++i])
	{
		ft_putnbr_fd(i + 1, 1);
		FT_PUTSTR("-> |");
		FT_PUTSTR(list->params[i]);
		FT_PUTSTR("|\n");
	}
	print_single_command(list->next);
}

void	print_cmd(t_piped_cmd *list)
{
	if (!list)
		return ;
	FT_PUTSTR("----- PIPE ------\n");
	// FT_PUTSTR(list->line);
	// FT_PUTSTR("|\n");
	print_single_command(list->single_command);
	print_cmd(list->next);
}

void	print_list(t_cmd *list)
{
	if (list)
	{
		FT_PUTSTR("----- |\n");
		// FT_PUTSTR(list->line);
		// FT_PUTSTR("|\n");
		print_cmd(list->cmd);
		print_list(list->next);
	}
}
