/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <aamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 12:40:06 by aamzil            #+#    #+#             */
/*   Updated: 2020/10/27 12:44:28 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	insert_commands(t_cmd *cmd_list, char quote, int *i, int *start)
{
	int j;
	int k;

	j = -1;
	k = (*i);
	while (!quote && g_pipe_cmd[++j])
	{
		if (g_pipe_cmd[j][0] == cmd_list->line[(*i)])
		{
			add_cmd(&cmd_list->cmd, ft_substr(cmd_list->line,
									(*start), (*i) - (*start)));
			(*start) = (*i) +
					is_redirection(g_pipe_cmd[j], cmd_list->line + (*i));
			(*i) += (!ft_strncmp(cmd_list->line + (*i), ">>", 2));
			break ;
		}
	}
}

void	treat_list(t_cmd *cmd_list)
{
	int		i;
	int		start;
	char	quote;

	if (!cmd_list)
		return ;
	if (check_pipes_error(&(cmd_list->line)))
		return ;
	i = -1;
	start = 0;
	quote = 0;
	while (cmd_list->line[++i])
	{
		if (cmd_list->line[i] == '\\' && ++i)
			continue;
		if ((cmd_list->line[i] == '\'' || cmd_list->line[i] == '"') && !quote)
			quote = cmd_list->line[i];
		else if (cmd_list->line[i] == quote)
			quote = 0;
		insert_commands(cmd_list, quote, &i, &start);
	}
	add_cmd(&cmd_list->cmd, ft_substr(cmd_list->line, start, i - start + 1));
	treat_list(cmd_list->next);
}
