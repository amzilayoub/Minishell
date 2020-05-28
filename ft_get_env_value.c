# include "minishell.h"

char	*ft_get_env_value(char *key, char **envp)
{
	int i;
	int len_key;
	char *env_value;

	i = -1;
	// to skip the dollar sign
	len_key = ft_strlen(++key);
	while (envp[++i])
	{
		if (!ft_strncmp(key, envp[i], len_key))
		{
			env_value = ft_substr(envp[i], len_key + 1, ft_strlen(envp[i]) - len_key - 1);
			add_mem(env_value);
			return (env_value);
		}
	}
	return (NULL);
}
