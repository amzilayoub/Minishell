# include "../minishell.h"

int	check_error(char **args)
{
	int i;
	int j;

	i = -1;
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
		{
			if (!(ft_isalnum(args[i][j]) || args[i][j] == '_'))
				return (1);
		}
	}
	return (0);
}

void	remove_env_var(char ***envp, int index)
{
	char *tmp;

	tmp = (*envp)[index];
	while ((*envp)[index])
	{
		(*envp)[index] = (*envp)[index + 1];
		index++;
	}
	free(tmp);
	free((*envp)[index]);
}

int	ft_unset(char **args, char ***envp)
{
	int i;
	int key_len;

	if (!(*args))
		return (0);
	if (check_error(args))
		FT_PUTSTR_ERR("bash : unset : not a valid identifier\n");
	i = -1;
	key_len = ft_strlen((*args));
	while ((*envp)[++i])
	{
		if (!ft_strncmp((*envp)[i], (*args), key_len) && (*envp)[i][key_len] == '=')
		{
			remove_env_var(envp, i);
			g_env_available_index--;
			break;
		}
	}
	ft_unset(args + 1, envp);
	return (0);
}
