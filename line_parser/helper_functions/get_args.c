# include "../../minishell.h"

int	get_arg_len(char *line)
{
	int i;
	int len;
	char quote;

	quote = 0;
	i = -1;
	len = ((*line) != 0);
	while (line[++i])
	{
		if (line[i] == '\\' && ++i)
			continue;
		if ((line[i] == '\'' || line[i] == '"') && !quote)
			quote = line[i];
		else if (line[i] == quote)
		{
			len++;
			quote = 0;
		}
		else if (!quote && line[i] == ' ')
		{
			i += skip_char(&line[i], ' ') - 1;
			len++;
		}
	}
	return (len);
}

char	**get_arg(char *line, char **envp)
{
	int i;
	char **args;
	char quote;
	int j;
	int start;
	char *tmp;

	i = -1;
	start = 0;
	j = -1;
	//printf("LEN = %i\n", get_arg_len(line));
	args = (char**)malloc(sizeof(char*) * (get_arg_len(line) + 1));
	quote = 0;
	while (line[++i])
	{
		if (line[i] == '\\')
		{
			if (!quote || line[i + 1] == '\\')
				shift_char(line + i);
			else if (quote && line[i + 1] == quote)
				shift_char(line + i);
		}
		else if (line[i] == '$')
			i += join_env_var(&line, i, envp);
		else if ((line[i] == '"' || line[i] == '\'') && !quote)
		{
			start = i + 1;
			quote = line[i];
		}
		else if (line[i] == quote && !(quote = 0))
		{
			args[++j] = ft_substr(line, start, i - start);
			start = i + 1;
		}
		else if (!quote && line[i] == ' '/* && (i += skip_char(line + i, ' ') - 1)*/)
		{
			if ((tmp = ft_substr(line, start, i - start))[0])
				args[++j] = tmp;
			else
				add_mem(tmp);
			i += skip_char(line + i, ' ') - 1;
			start = i + 1;
		}
	}
	if ((tmp = ft_substr(line, start, i - start))[0])
		args[++j] = tmp;
	else
		add_mem(tmp);
	args[++j] = NULL;
	i = -1;
	if (!args[0])
	{
		args[0] = ft_strdup("");
		args[1] = NULL;
	}
	return (args);
}
