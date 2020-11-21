/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_single_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 12:05:16 by aamzil            #+#    #+#             */
/*   Updated: 2020/11/10 12:05:18 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void		insert_commands(t_piped_cmd *list, char quote,
								int *i, int *start)
{
	int j;

	j = -1;
	while (!quote && g_pipe_cmd[++j])
	{
		if (g_pipe_cmd[j][0] == list->line[(*i)])
		{
			add_single_command(&list->single_command, ft_substr(list->line,
									(*start), (*i) - (*start)));
			(*start) = (*i) +
					is_redirection(g_pipe_cmd[j], list->line + (*i));
			(*i) += (!ft_strncmp(list->line + (*i), ">>", 2));
			break ;
		}
	}
}

void			treat_single_command_helper(t_piped_cmd *list)
{
	int		i;
	int		start;
	char	quote;

	if (!list)
		return ;
	i = -1;
	start = 0;
	quote = 0;
	while (list->line[++i])
	{
		if (list->line[i] == '\\' && list->line[i + 1] != '\'' && ++i)
			continue;
		if ((list->line[i] == '\'' || list->line[i] == '"') && !quote)
			quote = list->line[i];
		else if (list->line[i] == quote)
			quote = 0;
		insert_commands(list, quote, &i, &start);
	}
	add_single_command(&list->single_command,
						ft_substr(list->line, start, i - start + 1));
	treat_single_command_helper(list->next);
}

void			treat_single_command(t_cmd *cmd_list)
{
	if (!cmd_list)
		return ;
	treat_single_command_helper(cmd_list->cmd);
	treat_single_command(cmd_list->next);
}
