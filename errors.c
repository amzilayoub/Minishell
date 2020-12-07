/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <aamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 16:33:56 by aamzil            #+#    #+#             */
/*   Updated: 2020/10/19 12:48:44 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	set_error(char *error_msg)
{
	g_error_msg = error_msg;
	g_there_is_error = 1;
	return (g_there_is_error);
}

int		set_error_print(char *error_msg)
{
	set_error(error_msg);
	FT_PUTSTR_ERR(error_msg);
	return (THERE_IS_ERROR);
}

void	print_cmd_with_error(char *cmd, char *error_msg)
{
	FT_PUTSTR_ERR("Minishell ");
	FT_PUTSTR_ERR(cmd);
	FT_PUTSTR_ERR(" : ");
	FT_PUTSTR_ERR(error_msg);
	FT_PUTSTR_ERR("\n");
}
