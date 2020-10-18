# include "../../minishell.h"

int	join_env_var(char **str, int index, char **envp)
{
	int i;
	char *key;
	char *pre;
	char *suff;

	i = index + 1;
	if ((*str)[i] != '?')
	{
		while ((*str)[i] && (*str)[i] != '\\' && (*str)[i] != ' ' && ft_isalnum((*str)[i]))
			i++;
		key = ft_substr((*str), index, i - index);
		add_mem(key);
		if (!(key = ft_get_env_value(key, envp)))
			key = "";
		// else
		// 	add_mem(key);
	}
	else
	{
		i++;
		key = ft_itoa(WEXITSTATUS(g_status));
		add_mem(key);
	}
	pre = ft_substr((*str), 0, index);
	add_mem(pre);
	suff = ft_substr((*str), i, ft_strlen((*str)) - i);
	add_mem(suff);
	pre = ft_strjoin(pre, key);
	add_mem(pre);
	//add_mem((*str));
	(*str) = ft_strjoin(pre, suff);
	add_mem((*str));
	// substract 1 bcuz of the pre increment in the get_arg loop
	return (ft_strlen(key) - 1);
}
