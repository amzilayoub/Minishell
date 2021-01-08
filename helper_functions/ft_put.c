/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 17:04:45 by aamzil            #+#    #+#             */
/*   Updated: 2021/01/08 17:05:10 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putchar(char c)
{
	ft_putchar_fd(c, 1);
}

void	ft_putstr(char *str)
{
	ft_putstr_fd(str, 1);
}

void	ft_putstr_err(char *str)
{
	ft_putstr_fd(str, 2);
}
