/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print_single_var.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 16:18:47 by aamzil            #+#    #+#             */
/*   Updated: 2021/01/01 16:18:48 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	print_single_var(char *str)
{
	int i;

	i = -1;
	FT_PUTSTR("declare -x ");
	while (str[++i])
	{
		if (str[i] == '=')
			break ;
		FT_PUTCHAR(str[i]);
	}
	if (!str[i])
	{
		FT_PUTSTR("\n");
		return ;
	}
	FT_PUTSTR("=\"");
	while (str[++i])
		FT_PUTCHAR(str[i]);
	FT_PUTCHAR('"');
	FT_PUTSTR("\n");
}
