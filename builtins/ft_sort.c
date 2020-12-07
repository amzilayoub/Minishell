/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <aboutahr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 17:40:12 by aboutahr          #+#    #+#             */
/*   Updated: 2020/12/04 17:53:00 by aboutahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_cpyfree(char *d, char *s)
{
    d = ft_strdup(s);
    free(s);
}

char    **ft_sort(char **envp)
{
    int i;
	int c;
	char **sort;
	char *tmp;

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
		{
			if (ft_strcmp(sort[i], sort[c]) > 0)
			{
				tmp = ft_strdup(sort[i]);
				free(sort[i]);
                //ft_cpyfree(tmp = NULL, sort[i]);
				sort[i] = ft_strdup(sort[c]);
				free(sort[c]);
				sort[c] = ft_strdup(tmp);
				free(tmp);
			}
		}
	}
    return (sort);
}