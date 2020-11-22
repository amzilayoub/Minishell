/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <aamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 17:20:38 by aamzil            #+#    #+#             */
/*   Updated: 2020/10/26 11:47:16 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_key(char *str)
{
	int		i;
	char	*key;

	i = -1;
	if (ft_isdigit((*str)))
	{
		print_cmd_with_error("export", "Bad identifier !\n");
		return (NULL);
	}
	while (str[++i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_' || str[i] == '='))
		{
			FT_PUTSTR_ERR("bash : export : not a valid identifier");
			return (NULL);
		}
		if (str[i] == '=')
			break ;
	}
	if (!str[i])
		return (NULL);
	key = ft_substr(str, 0, i);
	add_mem(key);
	return (key);
}

void	env_append(char *str, char ***envp)
{
	int		i;
	char	**new_envp;

	if (g_env_available_index == g_env_len)
	{
		g_env_len += ARRAY_GROWTH;
		i = -1;
		new_envp = (char**)malloc(sizeof(char*) * (g_env_len + 1));
		while ((*envp)[++i])
		{
			new_envp[i] = ft_strdup((*envp)[i]);
			if (g_first_dup_env)
				free((*envp)[i]);
		}
		if (g_first_dup_env)
			free((*envp));
		new_envp[i] = NULL;
		g_first_dup_env = 1;
		g_envp = new_envp;
		(*envp) = new_envp;
	}
	(*envp)[g_env_available_index] = str;
	(*envp)[++g_env_available_index] = NULL;
}

int		print_env_vars(char **envp)
{
	int i;

	i = -1;
	while (envp[++i])
	{
		FT_PUTSTR("declare -x ");
		FT_PUTSTR(envp[i]);
		FT_PUTSTR("\n");
	}
	return (1);
}

int		compare_and_erase(char **args, char **envp, char *key, int len_key)
{
	if (!ft_strncmp((*envp), key, len_key) && (*envp)[len_key] == '=')
	{
		if (g_first_dup_env)
			add_mem((*envp));
		(*envp) = ft_strdup((*args));
		if (!g_first_dup_env)
			add_mem_perma((*envp));
		return (1);
	}
	return (0);
}

int		ft_export(char **args, char ***envp)
{
	int		i;
	char	*key;
	int		len_key;

	if (!(*args))
		return (print_env_vars((*envp)));
	if (!(key = get_key((*args))))
	{
		if (args[1])
			ft_export(&args[1], envp);
		return (1);
	}
	len_key = ft_strlen(key);
	i = -1;
	while ((*envp)[++i])
	{
		if (compare_and_erase(args, &(*envp)[i], key, len_key))
			break ;
	}
	if (!(*envp)[i])
		env_append(ft_strdup((*args)), envp);
	if (args[1])
		ft_export(&args[1], envp);
	return (0);
}
