/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 21:11:40 by aboutahr            #+#    #+#             */
/*   Updated: 2019/10/20 12:48:50 by aboutahr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	int				i;

	if (!len)
		return (b);
	i = -1;
	ptr = b;
	while (len--)
		ptr[++i] = (unsigned char)c;
	return (b);
}
