/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_single_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 12:20:48 by aamzil            #+#    #+#             */
/*   Updated: 2021/01/08 12:20:52 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int		print_env_vars(char **envp)
{
	int		i;

	i = -1;
	while (envp[++i])
		print_single_var(envp[i]);
	return (1);
}

void	print_single_var(char *str)
{
	int i;

	i = -1;
	ft_putstr("declare -x ");
	while (str[++i])
	{
		if (str[i] == '=')
			break ;
		ft_putchar(str[i]);
	}
	if (!str[i])
	{
		ft_putstr("\n");
		return ;
	}
	ft_putstr("=\"");
	while (str[++i])
		ft_putchar(str[i]);
	ft_putchar('"');
	ft_putstr("\n");
}
