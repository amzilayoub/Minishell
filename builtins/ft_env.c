/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <aboutahr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 17:18:14 by aboutahr            #+#    #+#             */
/*   Updated: 2020/10/19 13:17:40 by aboutahr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(char **args, char ***envp)
{
	int i;

	(void)args;
	i = -1;
	while ((*envp)[++i])
	{
		FT_PUTSTR((*envp)[i]);
		FT_PUTCHAR('\n');
	}
	return (0);
}
