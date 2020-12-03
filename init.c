/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <aboutahr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 16:37:08 by aboutahr            #+#    #+#             */
/*   Updated: 2020/10/26 11:25:50 by aboutahr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_builtins(void)
{
	g_cmd_char = ft_split("echo cd pwd export unset env exit >> > <", ' ');
	g_builtins[0] = &ft_echo;
	g_builtins[1] = &ft_cd;
	g_builtins[2] = &ft_pwd;
	g_builtins[3] = &ft_export;
	g_builtins[4] = &ft_unset;
	g_builtins[5] = &ft_env;
	g_builtins[6] = &ft_exit;
	g_builtins[7] = &ft_append_redir;
	g_builtins[8] = &ft_output_redir;
	g_builtins[9] = &ft_input_redir;
}

void	init_stdio(void)
{
	g_stdio_fd[0] = dup(0);
	g_stdio_fd[1] = dup(1);
	g_stdio_fd[2] = dup(2);
}

void	init_env_var(char **envp)
{
	g_env_len = 0;
	g_first_dup_env = 0;
	while (envp[g_env_len])
		g_env_len++;
	g_env_available_index = g_env_len;
}

void	init(char **envp)
{
	g_cmd_list = NULL;
	g_envp = NULL;
	g_pid = 0;
	g_is_piped = 0;
	g_mem_alloc = NULL;
	g_mem_perma = NULL;
	g_pipe_cmd = ft_split(">> > <", ' ');
	g_read_from_file = 0;
	init_builtins();
	init_stdio();
	init_env_var(envp);
	g_there_is_error = 0;
	g_error_msg = NULL;
}
