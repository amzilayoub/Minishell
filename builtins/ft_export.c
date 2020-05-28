# include "../minishell.h"

char	*get_key(char *str)
{
	int i;
	char *key;

	i = -1;
	while (str[++i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_' || str[i] == '='))
		{
			//error
			FT_PUTSTR_ERR("bash : export : not a valid identifier\n");
			return (NULL);
		}
		if (str[i] == '=')
			break;
	}
	if (!str[i])
		return (NULL);
	key = ft_substr(str, 0, i);
	add_mem(key);
	return (key);
}

char	**array_grow(char ***envp)
{
	int i;
	char **new_envp;

	g_env_len += ARRAY_GROWTH;
	i = -1;
	new_envp = (char**)malloc(sizeof(char*) * g_env_len + 1);
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
	return (new_envp);
}

void	env_append(char *str, char ***envp)
{
	if (g_env_available_index == g_env_len)
		(*envp) = array_grow(envp);
	(*envp)[g_env_available_index] = str;
	(*envp)[++g_env_available_index] = NULL;
}

int	ft_export(char **args, char ***envp)
{
	int i;
	char *key;
	int len_key;

	if (!(*args))
		return (1);
	if (!(key = get_key((*args))))
	{
		//error
		ft_export(&args[1], envp);
		return (1);
	}
	len_key = ft_strlen(key);
	//printf("KEY = %s\n", key);
	//printf("ARG = %s\n", *args);
	i = -1;
	while ((*envp)[++i])
	{
		//printf("%s\n", (*envp)[i]);
		if (!ft_strncmp((*envp)[i], key, len_key)/* && (*envp)[i][len_key] == '='*/)
		{
			(*envp)[i] = ft_strdup((*args));
			break;
		}
	}
	if (!(*envp)[i])
		env_append(ft_strdup((*args)), envp);
	//printf("LAST = %s | %c\n", (*envp)[i], (*envp)[i][len_key]);
	ft_export(&args[1], envp);
	return (0);
}
