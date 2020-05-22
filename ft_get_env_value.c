# include "minishell.h"

char	*ft_get_env_value(char *key, char **envp)
{
	int i;
	int len_key;

	i = -1;
	// to skip the dollar sign
	len_key = ft_strlen(++key);
	while (envp[++i])
	{
		if (!ft_strncmp(key, envp[i], len_key))
			return (ft_substr(envp[i], len_key + 1, ft_strlen(envp[i]) - len_key - 1));
	}
	return (NULL);
}
