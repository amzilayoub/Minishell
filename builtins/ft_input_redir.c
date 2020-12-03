/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <aboutahr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 19:49:16 by aboutahr            #+#    #+#             */
/*   Updated: 2020/10/19 13:18:20 by aboutahr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_input_redir(char **args, char ***envp)
{
	int fd;
	int i;

	(void)envp;
	i = 0;
	if (!(*args))
		return (set_error_print("bash : syntax error\n"));
	while (args[i])
		i++;
	if ((fd = open(args[i - 1], O_RDONLY)) < 0)
	{
		FT_PUTSTR_ERR("bash : can't open this File\n");
		return (1);
	}
	g_read_from_file = 1;
	dup2(fd, 0);
	close(fd);
	return (0);
}
