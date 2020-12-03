/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 22:03:17 by aboutahr            #+#    #+#             */
/*   Updated: 2019/10/20 12:51:28 by aboutahr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*ptr;

	i = -1;
	ptr = 0;
	while (s[++i])
	{
		if (s[i] == c)
			ptr = (char*)&s[i];
	}
	if (s[i] == c)
		return ((char*)&s[i]);
	return ((char*)ptr);
}
