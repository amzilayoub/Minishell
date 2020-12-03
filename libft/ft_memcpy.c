/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 21:16:13 by aboutahr            #+#    #+#             */
/*   Updated: 2019/10/20 14:25:15 by aboutahr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*pdst;
	unsigned char	*psrc;
	size_t			i;

	i = -1;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst == src)
		return (dst);
	pdst = (unsigned char*)dst;
	psrc = (unsigned char*)src;
	if (!ft_memcmp(dst, src, n))
		return (dst);
	if (!n)
		return (dst);
	while (++i < n)
		pdst[i] = psrc[i];
	return (dst);
}
