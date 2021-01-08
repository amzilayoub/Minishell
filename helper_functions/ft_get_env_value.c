/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <aamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 16:35:13 by aamzil            #+#    #+#             */
/*   Updated: 2020/10/19 11:00:32 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** This line :len_key = ft_strlen(++key);
** is to skip the dollar sign
*/

char	*ft_get_env_value(char *key, char **envp)
{
	int		i;
	int		len_key;
	char	*env_value;

	i = -1;
	len_key = ft_strlen(++key);
	if (!(*key))
		return (--key);
	while (envp[++i])
	{
		if (!ft_strncmp(key, envp[i], len_key))
		{
			env_value = ft_substr(
				envp[i],
				len_key + 1,
				ft_strlen(envp[i]) - len_key - 1);
			add_mem(env_value);
			return (env_value);
		}
	}
	if (!ft_isdigit((*key)))
		return (NULL);
	return (key);
}
