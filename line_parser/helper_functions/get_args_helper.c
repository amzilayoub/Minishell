/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:22:15 by aamzil            #+#    #+#             */
/*   Updated: 2021/01/08 15:22:17 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		get_arg_len(char *line)
{
	int		i;
	int		len;
	char	quote;

	quote = 0;
	i = -1;
	len = ((*line) != 0);
	while (line[++i])
	{
		if (line[i] == '\\' && ++i)
			continue;
		if ((line[i] == '\'' || line[i] == '"') && !quote)
			quote = line[i];
		else if (line[i] == quote && ++len)
			quote = 0;
		else if (!quote && (line[i] == ' ' || line[i] == '>' || line[i] == '<'))
		{
			i += skip_char(&line[i], ' ');
			i += (line[i] == '>' || line[i] == '<');
			i += (line[i] == '>');
			i -= 1;
			len++;
		}
	}
	return (len);
}

void	insert_arg(t_arg_manip *vars, char **line, char ***args)
{
	char *tmp;

	if (!vars->quote && (*line)[vars->i] == ' ')
	{
		if ((tmp = ft_substr((*line), vars->start, vars->i - vars->start))[0])
			(*args)[++vars->j] = tmp;
		else
			add_mem(tmp);
		vars->space = vars->i;
		vars->i += skip_char((*line) + vars->i, ' ') - 1;
		vars->start = vars->i + 1;
	}
	else if (!vars->quote &&
			((*line)[vars->i] == '>' || (*line)[vars->i] == '<'))
	{
		(*args)[++vars->j] = ft_substr((*line), vars->i, 1 +
				((*line)[vars->i + 1] == '>'));
		vars->i += 1 + ((*line)[vars->i + 1] == '>');
		vars->i += skip_char((*line) + vars->i, ' ') - 1;
		vars->start = vars->i + 1;
	}
}

/*
** this code to treat params like that echo hello"Sdfsdfsdf"
** tmp = ft_substr((*line), vars->space + 1,
** 				vars->start - vars->space - 2);
** (*args)[vars->j] = ft_strjoin(tmp, (*args)[vars->j]);
*/

void	quotes_checks(t_arg_manip *vars, char **line, char ***args)
{
	if ((*line)[vars->i] == vars->quote && !(vars->quote = 0))
	{
		shift_char((*line) + vars->i);
		vars->i--;
	}
	else
		insert_arg(vars, line, args);
}

int		skip_backslash(t_arg_manip *vars, char **line)
{
	if (vars->quote != '\'' &&
		(*line)[vars->i] == '\\' &&
		(*line)[vars->i + 1] == '\\')
		shift_char((*line) + vars->i);
	else if (vars->quote != '\'' &&
			(*line)[vars->i] == '\\' &&
			(*line)[vars->i + 1] == '"')
		shift_char((*line) + vars->i);
	else if (vars->quote != '\'' &&
			(*line)[vars->i] == '\\' &&
			(*line)[vars->i + 1] == '$')
		shift_char((*line) + vars->i);
	else if (!vars->quote &&
			(*line)[vars->i] == '\\' &&
			(*line)[vars->i + 1] == '\'')
		shift_char((*line) + vars->i);
	else if (vars->quote == '"' &&
			(*line)[vars->i] == '\\' &&
			(*line)[vars->i + 1] != '\'')
		shift_char((*line) + vars->i);
	else
		return (0);
	return (1);
}

void	get_arg_helper(t_arg_manip *vars, char **line,
						char ***envp, char ***args)
{
	while ((*line)[++vars->i])
	{
		if (skip_backslash(vars, line))
			continue ;
		else if ((*line)[vars->i] == '$' && vars->quote != '\'')
			vars->i += join_env_var(line, vars->i, envp);
		else if (((*line)[vars->i] == '"' ||
			(*line)[vars->i] == '\'') && !vars->quote)
		{
			vars->quote = (*line)[vars->i];
			shift_char((*line) + vars->i);
			vars->i--;
		}
		else
			quotes_checks(vars, line, args);
	}
}
