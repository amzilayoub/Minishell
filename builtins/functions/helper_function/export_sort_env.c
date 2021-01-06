/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <aboutahr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 17:40:12 by aboutahr          #+#    #+#             */
/*   Updated: 2021/01/01 16:18:55 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	ft_cpyfree(char **d, char **s)
{
	char *tmp;

	tmp = ft_strdup(*d);
	free(*d);
	*d = ft_strdup(*s);
	free(*s);
	*s = ft_strdup(tmp);
	free(tmp);
}

char	**ft_sort(char **envp)
{
	int		i;
	int		c;
	char	**sort;

	i = -1;
	c = 0;
	while (envp[c])
		c++;
	sort = (char**)malloc(sizeof(char*) * (c + 1));
	c = -1;
	while (envp[++c])
	{
		sort[c] = malloc(ft_strlen(envp[c] + 1));
		sort[c] = strcpy(sort[c], envp[c]);
	}
	sort[c] = NULL;
	while (sort[++i])
	{
		c = i;
		while (sort[++c])
			if (ft_strcmp(sort[i], sort[c]) > 0)
				ft_cpyfree(&sort[i], &sort[c]);
	}
	return (sort);
}
