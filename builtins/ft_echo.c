# include "../minishell.h"

int	new_line(char **args)
{
	int i;

	i = -1;
	if ((*args) && !ft_strncmp((*args), "-n", 2))
		return (0);
	return (1);
}

void	ft_echo(char **args, char ***envp)
{
	int i;
	int nl;

	nl = new_line(args);
	i = (nl) ? -1 : 0;
	while (args[++i])
	{
		FT_PUTSTR(args[i]);
		if (args[i + 1])
			FT_PUTCHAR(' ');
	}
	if (new_line(args))
		FT_PUTCHAR('\n');
}
