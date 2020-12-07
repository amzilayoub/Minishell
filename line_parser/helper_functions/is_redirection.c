/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <aamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 11:56:08 by aamzil            #+#    #+#             */
/*   Updated: 2020/10/19 11:56:11 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_redirection(char *red, char *line)
{
	if (!ft_strncmp(red, ">>", 2))
		return (0);
	else if (red[0] == '>' || red[0] == '<')
		return (0);
	else
		return (1 + skip_char(line + 1, ' '));
}
