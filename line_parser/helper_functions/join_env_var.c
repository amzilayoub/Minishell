/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_env_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <aamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 11:56:24 by aamzil            #+#    #+#             */
/*   Updated: 2020/10/19 12:01:59 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
** This function join the line with the env variable
** NOTE : i substract 1 from the returb value,
** because the function which is going to recieve the value
** has a pre_increment
*/

void	concat_vars(char **str, char *key, int i, int index)
{
	char	*pre;
	char	*suff;

	pre = ft_substr((*str), 0, index);
	add_mem(pre);
	suff = ft_substr((*str), i, ft_strlen((*str)) - i);
	add_mem(suff);
	pre = ft_strjoin(pre, key);
	add_mem(pre);
	(*str) = ft_strjoin(pre, suff);
	add_mem((*str));
}

int		join_env_var(char **str, int index, char **envp)
{
	int		i;
	char	*key;

	i = index + 1;
	if ((*str)[i] != '?')
	{
		while ((*str)[i] && (*str)[i] != '\\' &&
				(*str)[i] != ' ' && ft_isalnum((*str)[i]))
			i++;
		key = ft_substr((*str), index, i - index);
		add_mem(key);
		if (!(key = ft_get_env_value(key, envp)))
			key = "";
	}
	else
	{
		i++;
		if (g_error_n)
			key = ft_itoa(g_error_n);
		else
			key = ft_itoa(WEXITSTATUS(g_status));
		add_mem(key);
	}
	concat_vars(str, key, i, index);
	return (ft_strlen(key) - 1);
}
