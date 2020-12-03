/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 18:46:26 by aboutahr            #+#    #+#             */
/*   Updated: 2019/10/19 17:20:42 by aboutahr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	if (*alst == (void*)0)
		(*alst) = new;
	else
	{
		if ((*alst)->next)
			ft_lstadd_back(&(*alst)->next, new);
		else
			(*alst)->next = new;
	}
}
