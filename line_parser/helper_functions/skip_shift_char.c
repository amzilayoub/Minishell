# include "../../minishell.h"

char	*shift_char(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		str[i] = str[i + 1];
	return (str);
}

int	skip_char(char *line, char c)
{
	int i;

	i = 0;
	while (line[i] == c)
		i++;
	return (i);
}

