/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management_helper.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 02:49:45 by aboutahr            #+#    #+#             */
/*   Updated: 2020/11/06 02:49:53 by aboutahr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_mem_perma_helper(t_mem_alloc **list, void *mem)
{
	if ((*list))
		add_mem_perma_helper(&(*list)->next, mem);
	else
	{
		(*list) = (t_mem_alloc*)malloc((sizeof(t_mem_alloc)));
		(*list)->mem = mem;
		(*list)->next = NULL;
	}
}

void	add_mem_perma(void *mem)
{
	add_mem_perma_helper(&g_mem_perma, mem);
}

void	add_mem_helper(t_mem_alloc **list, void *mem)
{
	if ((*list))
		add_mem_helper(&(*list)->next, mem);
	else
	{
		(*list) = (t_mem_alloc*)malloc((sizeof(t_mem_alloc)));
		(*list)->mem = mem;
		(*list)->next = NULL;
	}
}

void	add_mem(void *mem)
{
	add_mem_helper(&g_mem_alloc, mem);
}
