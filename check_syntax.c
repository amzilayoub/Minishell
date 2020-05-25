# include "minishell.h"

char	check_semicolons(char *line)
{
	int i;
	int start;
	char quote;

	g_there_is_error = 0;
	i = skip_char(line, ' ') - 1;
	if (line[i + 1] == ';')
		return (set_error("Minishell: syntax error near to ';'\n"));
	quote = 0;
	while (line[++i])
	{
		if (line[i] == '\\' && ++i)
			continue;
		if ((line[i] == '"' || line[i] == '\'') && !quote)
			quote = line[i];
		else if (line[i] == quote)
			quote = 0;
		if (!quote && line[i] == ';')
		{
			i += skip_char(line + i + 1, ' ');
			if (line[i + 1] == ';' || line[i + 1] == '|')
				return (set_error("Minishell: syntax error near to ';'\n"));
		}
	}
	return (0);
}


// exemple echo hh || echo test => hh
// : echo hello ||| echo test => error
// : echo hello |  | echo tattoor => error


void	remove_useless_cmd(char **line, int index)
{
	if (index)
		(*line) = ft_substr((*line), 0, index);
}

char	check_pipes_error(char **line)
{
	int i;
	int first_double_pipe;
	int quote;

	i = skip_char((*line), ' ') - 1;
	if ((*line)[i + 1] == '|')
		return (set_error("Minishell: syntax error near to '|'\n"));
	first_double_pipe = 0;
	quote = 0;
	while ((*line)[++i])
	{
		if ((*line)[i] == '\\' && ++i)
			continue;
		if (((*line)[i] == '"' || (*line)[i] == '\'') && !quote)
			quote = (*line)[i];
		else if ((*line)[i] == quote)
			quote = 0;
		if (!quote && (*line)[i] == '|')
		{
			if ((*line)[i + 1] == '|' && ++i)
			{
				first_double_pipe = (first_double_pipe) ? first_double_pipe : i - 1;
				i += skip_char(&(*line)[i + 1], ' ');
				if ((*line)[i + 1] == '|')
					return (set_error("Minishell: syntax error near to '|'\n"));
			}
			else
			{
				i += skip_char((*line) + i + 1, ' ');
				if ((*line)[i + 1] == '|' || !(*line)[i + 1])
					return (set_error("Minishell: syntax error near to '|'\n"));
			}
		}
	}
	remove_useless_cmd(line, first_double_pipe);
	return (0);
}
