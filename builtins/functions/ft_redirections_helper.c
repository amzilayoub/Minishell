/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <aamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 19:50:44 by aamzil            #+#    #+#             */
/*   Updated: 2020/10/31 11:03:00 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	write_to_file(char **args, char *text, int new_line, int fd)
{
	char	*tmp;
	int		i;

	i = 0;
	while (args[++i])
	{
		tmp = ft_strjoin(" ", args[i]);
		text = ft_strjoin(text, tmp);
		add_mem(text);
		add_mem(tmp);
	}
	if (!g_next_cmd || g_next_cmd[0] != '>')
	{
		ft_putstr_fd(text, fd);
		if (new_line)
			ft_putchar_fd('\n', fd);
	}
	ft_putstr_fd(text, 1);
	if (new_line)
		ft_putchar_fd('\n', 1);
}

void	redirection_read_function(char **args, int fd)
{
	char	*text;
	char	*line;
	int		i;
	int		new_line;

	text = "";
	line = (char*)malloc(BUFFER_TO_READ + 1);
	while ((i = read(0, line, BUFFER_TO_READ)) > 0)
	{
		line[i] = '\0';
		text = ft_strjoin(text, line);
		add_mem(text);
	}
	add_mem(line);
	new_line = 0;
	if (args[1] && (new_line = (text[ft_strlen(text) - 1] == '\n')))
		text[ft_strlen(text) - 1] = '\0';
	write_to_file(args, text, new_line, fd);
	close(fd);
}

int		ft_redirections_helper(char **args, int flags)
{
	int fd;

	if (!(*args))
		return (set_error_print("bash : syntax error\n", 258));
	if ((fd = open(args[0], flags, 0777)) < 0)
	{
		FT_PUTSTR_ERR("bash : can't open this File\n");
		return (errno);
	}
	if (g_is_piped)
		redirection_read_function(args, fd);
	return (0);
}
