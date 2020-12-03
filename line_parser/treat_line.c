/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <aboutahr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 12:38:41 by aboutahr            #+#    #+#             */
/*   Updated: 2020/10/26 11:32:05 by aboutahr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	treat_line(char *line)
{
	int		i;
	int		start;
	char	quote;

	i = skip_char(line, ' ') - 1;
	start = skip_char(line, ' ');
	quote = 0;
	while (line[++i])
	{
		if (line[i] == '\\' && line[i + 1] != '\'' && ++i)
			continue;
		if ((line[i] == '"' || line[i] == '\'') && !quote)
			quote = line[i];
		else if (quote && line[i] == quote)
			quote = 0;
		else if (!quote && line[i] == ';')
		{
			create_cmd_list(&g_cmd_list, ft_substr(line, start, i - start));
			i += skip_char(line + i + 1, ' ');
			start = i + 1;
		}
	}
	create_cmd_list(&g_cmd_list, ft_substr(line, start, i + 1 - start));
}
