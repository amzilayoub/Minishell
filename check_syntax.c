/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <aboutahr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 16:16:17 by aboutahr            #+#    #+#             */
/*   Updated: 2020/10/19 13:10:06 by aboutahr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	check_semicolons(char *line)
{
	int		i;
	char	quote;

	g_there_is_error = 0;
	i = skip_char(line, ' ') - 1;
	if (line[i + 1] == ';')
		return (set_error("Minishell: syntax error near to ';'\n"));
	quote = 0;
	while (line[++i])
	{
		if (line[i] == '\\' && line[i + 1] != '\'' && ++i)
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

void	remove_useless_cmd(char **line, int index)
{
	if (index)
	{
		add_mem((*line));
		(*line) = ft_substr((*line), 0, index);
	}
}

char	check_pipes_error_helper(char **line, int *i, int *first_double_pipe)
{
	if ((*line)[(*i) + 1] == '|' && (*i))
	{
		if (!(*first_double_pipe))
			(*first_double_pipe) = (*i) - 1;
		(*i) += skip_char(&(*line)[(*i) + 1], ' ');
		if ((*line)[(*i) + 1] == '|')
			return (set_error("Minishell: syntax error near to '|'\n"));
	}
	else
	{
		(*i) += skip_char((*line) + (*i) + 1, ' ');
		if ((*line)[(*i) + 1] == '|' || !(*line)[(*i) + 1])
			return (set_error("Minishell: syntax error near to '|'\n"));
	}
	return (0);
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
		if ((*line)[i] == '\\' && (*line)[i + 1] != '\'' && ++i)
			continue;
		if (((*line)[i] == '"' || (*line)[i] == '\'') && !quote)
			quote = (*line)[i];
		else if ((*line)[i] == quote)
			quote = 0;
		if (!quote && (*line)[i] == '|')
			if (check_pipes_error_helper(line, &i, &first_double_pipe))
				return (g_there_is_error);
	}
	remove_useless_cmd(line, first_double_pipe);
	return (0);
}
