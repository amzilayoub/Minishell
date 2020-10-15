# include "../minishell.h"

void	treat_line(char *line)
{
	int		i;
	int		start;
	char	quote;

	i = -1;
	start = 0;
	quote = 0;
	while (line[++i])
	{
		if (line[i] == '\\')
		{
			i++;
			continue;
		}
		if ((line[i] == '"' || line[i] == '\'') && !quote)
			quote = line[i];
		else if (quote && line[i] == quote)
			quote = 0;
		else if (!quote && line[i] == ';')
		{
			create_cmd_list(&g_cmd_list, ft_substr(line, start, i - start));
			start = i + 1;
		}
	}
	create_cmd_list(&g_cmd_list, ft_substr(line, start, i + 1 - start));
}
