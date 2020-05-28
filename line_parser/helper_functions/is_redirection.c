# include "../../minishell.h"

int	is_redirection(char *red, char *line)
{
	if (!ft_strncmp(red, ">>", 2))
		return (0);
	else if (red[0] == '>' || red[0] == '<')
		return (0);
	else
		return (1 + skip_char(line + 1, ' '));
}
