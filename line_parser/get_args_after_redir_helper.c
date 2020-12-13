/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args_after_redir_helper.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 18:13:20 by aamzil            #+#    #+#             */
/*   Updated: 2020/11/21 18:40:38 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		find_redirection(char *line, int n)
{
	int		i;
	char	quote;

	i = -1;
	quote = 0;
	while (line[++i])
	{
		if (line[i] == '\\' && ++i)
			continue ;
		if ((line[i] == '"' || line[i] == '\'') && !quote)
			quote = line[i];
		else if (line[i] == quote)
			quote = 0;
		else if (!quote && (line[i] == '>' || line[i] == '<'))
		{
			if (n == 0)
				return (i);
			if (line[i + 1] == '>')
				++i;
			n--;
		}
	}
	return (-1);
}

int		skip_file_name(char *line)
{
	int		i;
	char	quote;

	quote = 0;
	i = skip_char(line, ' ') - 1;
	while (line[++i])
	{
		if (line[i] == '\\' && ++i)
			continue ;
		if ((line[i] == '"' || line[i] == '\'') && !quote)
			quote = line[i];
		else if (line[i] == quote)
			quote = 0;
		else if (!quote && line[i] == ' ')
			break ;
	}
	return (i);
}

/*
** This function reordering the commands
** ex : echo hello > file wc
** should be : echo hello wc > file
** Step One : joining the command with the argument and i mean by that
** joining "echo hello" with wc to be "echo hello wc"
** Step two : joining the redirection with the whole command
** so it will be "echo hello wc > file"
*/

void	join_lines_helper(
							t_piped_cmd *list,
							int filename,
							int end,
							int *where_to_cut)
{
	char	*pre;
	char	*suff;
	int		tmplen;

	pre = ft_substr(list->line, 0, (*where_to_cut));
	suff = ft_substr(list->line, filename, abs(filename - end));
	add_mem(pre);
	add_mem(suff);
	pre = ft_strjoin(pre, suff);
	add_mem(pre);
	tmplen = ft_strlen(pre);
	suff = ft_substr(list->line, (*where_to_cut), filename - (*where_to_cut));
	pre = ft_strjoin(pre, suff);
	add_mem(pre);
	add_mem(suff);
	add_mem(list->line);
	list->line = ft_strjoin(pre, list->line + filename + abs(filename - end));
	(*where_to_cut) = tmplen;
}

void	join_lines(t_piped_cmd *list, int i, int start, int *where_to_cut)
{
	int		end;
	int		filename;

	filename = start + 1 + (list->line[start + 1] == '>');
	filename += skip_file_name(list->line + filename);
	if ((end = find_redirection(list->line, i + 1)) == -1)
		end = ft_strlen(list->line);
	join_lines_helper(list, filename, end, where_to_cut);
}

void	get_args_after_redir_helper(t_piped_cmd *list)
{
	int		start;
	int		i;
	int		where_to_cut;

	if (!list)
		return ;
	i = 0;
	where_to_cut = find_redirection(list->line, i);
	while ((start = find_redirection(list->line, i)) != -1)
	{
		join_lines(list, i, start, &where_to_cut);
		i++;
	}
	get_args_after_redir_helper(list->next);
}
