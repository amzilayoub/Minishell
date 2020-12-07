/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <aamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 19:50:20 by aamzil            #+#    #+#             */
/*   Updated: 2020/10/19 13:19:01 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getcwd(void)
{
	int		nb;
	char	*old_path;
	char	*path;

	nb = 50;
	path = ft_strdup(".");
	old_path = ft_strdup("");
	while (ft_strcmp(path, old_path))
	{
		free(old_path);
		old_path = ft_strdup(path);
		free(path);
		path = (char*)malloc(nb + 1);
		path[nb] = 0;
		getcwd(path, nb);
		nb *= 2;
	}
	free(old_path);
	return (path);
}

int		ft_pwd(char **args, char ***envp)
{
	char *wd;

	(void)args;
	(void)envp;
	wd = ft_getcwd();
	FT_PUTSTR(wd);
	FT_PUTCHAR('\n');
	free(wd);
	return (1);
}
