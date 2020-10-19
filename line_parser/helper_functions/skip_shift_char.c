/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_shift_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <aamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 12:03:07 by aamzil            #+#    #+#             */
/*   Updated: 2020/10/19 12:03:18 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*shift_char(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		str[i] = str[i + 1];
	return (str);
}

int		skip_char(char *line, char c)
{
	int i;

	i = 0;
	while (line[i] == c)
		i++;
	return (i);
}
