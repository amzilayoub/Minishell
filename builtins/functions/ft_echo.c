/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <aamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 17:17:41 by aamzil            #+#    #+#             */
/*   Updated: 2020/10/19 13:17:24 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	new_line(char **args)
{
	if ((*args) && !ft_strncmp((*args), "-n", 2))
		return (0);
	return (1);
}

int	ft_echo(char **args, char ***envp)
{
	int i;
	int nl;

	(void)envp;
	nl = new_line(args);
	i = (nl) ? -1 : 0;
	while (args[++i])
	{
		ft_putstr(args[i]);
		if (args[i + 1])
			ft_putchar(' ');
	}
	if (new_line(args))
		ft_putchar('\n');
	return (0);
}
