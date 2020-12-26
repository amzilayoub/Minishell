/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <aamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 17:18:14 by aamzil            #+#    #+#             */
/*   Updated: 2020/10/19 13:17:40 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(char **args, char ***envp)
{
	int i;

	(void)args;
	i = -1;
	while ((*envp)[++i])
	{
		if (!ft_strchr((*envp)[i], '='))
			continue ;
		FT_PUTSTR((*envp)[i]);
		FT_PUTCHAR('\n');
	}
	return (0);
}


int		main(int argc, char **argv, char **envp)
{
	(void)argc;
	ft_env(argv, &envp);
	return (0);
}