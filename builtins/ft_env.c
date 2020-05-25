# include "../minishell.h"

int	ft_env(char **args, char ***envp)
{
	int i;

	i = -1;
	while ((*envp)[++i])
	{
		FT_PUTSTR((*envp)[i]);
		FT_PUTCHAR('\n');
	}
	return (0);
}
